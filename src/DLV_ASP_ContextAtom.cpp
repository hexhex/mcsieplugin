/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2009,2010  Markus Boegl
 * Copyright (C) 2011,2012  Peter Schueller
 * 
 * This file is part of dlvhex-mcs-equilibrium-plugin.
 *
 * dlvhex-mcs-equilibrium-plugin is free software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * dlvhex-mcs-equilibrium-plugin is distributed in the hope that it will
 *  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dlvhex-dlplugin; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


/**
 * @file   DLV_ASP_ContextAtom.cpp
 * @author Markus Boegl
 * @author Peter Schueller
 * @date   Sun Jan 24 13:38:47 2010
 * 
 * @brief  Context to use ASP Programs
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "DLV_ASP_ContextAtom.h"
//#include "Timing.h"

#include <dlvhex2/Logger.h>
#include <dlvhex2/Registry.h>
#include <dlvhex2/Printhelpers.h>
#include <dlvhex2/Printer.h>
#include <dlvhex2/InputProvider.h>
#include <dlvhex2/ProgramCtx.h>
#include <dlvhex2/HexParser.h>
#include <dlvhex2/ASPSolverManager.h>
//#include <dlvhex/ProgramCtx.h>
//#include <dlvhex2/DLVProcess.h>
#include <dlvhex2/ASPSolver.h>

namespace dlvhex {
namespace mcsdiagexpl {

using namespace std;

void
DLV_ASP_ContextAtom::retrieve(const Query& query, Answer& answer)
{
  LOG_SCOPE(INFO,"DACA::r",false);
  LOG(INFO,"DLV_ASP_ContextAtom::retrieve");

  // query.input is tuple [context_id,belief_pred,input_pred,outputs_pred,program]

  // we use an extra registry for this external program
  ProgramCtx kbctx;
  kbctx.setupRegistry(RegistryPtr(new Registry));

  // parse kb into kbctx
  {
    // get name of context program
    const std::string& programStr = registry->terms.getByID(query.input[4]).symbol;

    // remove quotes
    assert(programStr[0] == '"' && programStr[programStr.size()-1] == '"');
    std::string program;
    if( !pcd.path().empty() )
      program += pcd.path();
    program += programStr.substr(1, programStr.size()-2);

    LOG(DBG,"parsing context kb for program '" << program << "'");

    // build input
    InputProviderPtr input(new InputProvider);
    input->addFileInput(program);

    // parse
    ModuleHexParser parser;
    parser.parse(input, kbctx);
  }
  DBGLOG(DBG,"after parsing input: idb and edb are" << std::endl << std::endl <<
      printManyToString<RawPrinter>(kbctx.idb,"\n",kbctx.registry()) << std::endl <<
      *kbctx.edb << std::endl);

  // aset = belief_pred, bset = inputs_pred, oset = outputs_pred
  StringSet aset, bset, oset;
  convertQueryToStringSets(query,aset,bset,oset);

  // add inputs (= bridge rule heads) to program
  {
		for(StringSet::const_iterator inp = bset.begin(); inp != bset.end(); ++inp)
    {
      // add symbol to program as fact
			Term inputTerm(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, *inp);

      // create term symbol (this is now another registry!) and add
      ID kbInputTermID = kbctx.registry()->terms.getIDByString(inputTerm.symbol);
      if( kbInputTermID == ID_FAIL )
        kbInputTermID = kbctx.registry()->terms.storeAndGetID(inputTerm);
      DBGLOG(DBG,"in kbctx this term has id " << kbInputTermID);

      // create unary fact (this is now another registry!)
      OrdinaryAtom kboatom(ID::MAINKIND_ATOM | ID::SUBKIND_ATOM_ORDINARYG);
      kboatom.tuple.push_back(kbInputTermID);
      kboatom.text = inputTerm.symbol;
      ID kbInputFactID = kbctx.registry()->ogatoms.getIDByTuple(kboatom.tuple);
      if( kbInputFactID == ID_FAIL )
        kbInputFactID = kbctx.registry()->ogatoms.storeAndGetID(kboatom);
      DBGLOG(DBG,"in kbctx this fact has id " << kbInputFactID);

      // add to edb
      kbctx.edb->setFact(kbInputFactID.address);
    }
  }
  DBGLOG(DBG,"after adding inputs: kbctx.edb is " << *kbctx.edb);

  // calculate set differences and add constraints
  StringSet ainoset, ominusaset;
  {
    typedef std::insert_iterator<StringSet> Inserter;
    {
      Inserter ominusainsert(ominusaset, ominusaset.begin());
      std::set_difference(oset.begin(), oset.end(), aset.begin(), aset.end(), ominusainsert);
    }
    {
      Inserter ainoinsert(ainoset, ainoset.begin());
      std::set_intersection(aset.begin(), aset.end(), oset.begin(), oset.end(), ainoinsert);
    }

    // add O - A as Constraint ":- x."
    // => enforce that beliefs not in A are not there
    DBGLOG(DBG,"enforcing the following beliefs to be absent: " << printrange(ominusaset));
    for(StringSet::const_iterator it = ominusaset.begin();
        it != ominusaset.end(); ++it)
    {
      // term
      Term t(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, *it);
      ID kbidt = kbctx.registry()->terms.getIDByString(t.symbol);
      if( kbidt == ID_FAIL )
        kbidt = kbctx.registry()->terms.storeAndGetID(t);

      // ordinary atom
      OrdinaryAtom oa(ID::MAINKIND_ATOM | ID::SUBKIND_ATOM_ORDINARYG);
      oa.tuple.push_back(kbidt);
      oa.text = *it;
      ID kbidoa = kbctx.registry()->ogatoms.getIDByTuple(oa.tuple);
      if( kbidoa == ID_FAIL )
        kbidoa = kbctx.registry()->ogatoms.storeAndGetID(oa);

      // constraint :- *it.
      Rule constraint(ID::MAINKIND_RULE | ID::SUBKIND_RULE_CONSTRAINT);
      constraint.body.push_back(ID::posLiteralFromAtom(kbidoa));
      ID kbidconstraint = kbctx.registry()->rules.storeAndGetID(constraint);
      kbctx.idb.push_back(kbidconstraint);
    }

    // add A - O as Constraint ":- not x."
    // => enforce that beliefs in A are there
    DBGLOG(DBG,"enforcing the following beliefs to be present: " << printrange(ainoset));
    for(StringSet::const_iterator it = ainoset.begin();
        it != ainoset.end(); ++it)
    {
      // term
      Term t(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, *it);
      ID kbidt = kbctx.registry()->terms.getIDByString(t.symbol);
      if( kbidt == ID_FAIL )
        kbidt = kbctx.registry()->terms.storeAndGetID(t);

      // ordinary atom
      OrdinaryAtom oa(ID::MAINKIND_ATOM | ID::SUBKIND_ATOM_ORDINARYG);
      oa.tuple.push_back(kbidt);
      oa.text = *it;
      ID kbidoa = kbctx.registry()->ogatoms.getIDByTuple(oa.tuple);
      if( kbidoa == ID_FAIL )
        kbidoa = kbctx.registry()->ogatoms.storeAndGetID(oa);

      // constraint :- not *it.
      Rule constraint(ID::MAINKIND_RULE | ID::SUBKIND_RULE_CONSTRAINT);
      constraint.body.push_back(ID::nafLiteralFromAtom(kbidoa));
      ID kbidconstraint = kbctx.registry()->rules.storeAndGetID(constraint);
      kbctx.idb.push_back(kbidconstraint);
    }
  }

  // check if there is one answer set, if yes return true, false otherwise
  {
    typedef ASPSolverManager::SoftwareConfiguration<ASPSolver::DLVSoftware> DLVConfiguration;
    DLVConfiguration dlv;
    ASPProgram program(kbctx.registry(), kbctx.idb, kbctx.edb, kbctx.maxint);
    LOG(DBG,"context program:" << std::endl << 
      printManyToString<RawPrinter>(kbctx.idb,"\n",kbctx.registry()) << std::endl <<
      *kbctx.edb << std::endl);
    ASPSolverManager mgr;
    ASPSolverManager::ResultsPtr res = mgr.solve(dlv, program);
    AnswerSet::Ptr firstAnswerSet = res->getNextAnswerSet();
    if( firstAnswerSet != 0 )
    {
      LOG(DBG,"got answer set " << *firstAnswerSet->interpretation);
      // accept -> add tuple
      answer.get().push_back(Tuple());
    }
    else
    {
      LOG(DBG,"got no answer set!");
      // did not accept -> mark as used nevertheless
      answer.use();
    }
  }
}

} // namespace mcsdiagexpl
} // namespace dlvhex
