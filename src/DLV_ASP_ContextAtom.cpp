/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2009,2010  Markus Boegl
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
 * @date   Sun Jan 24 13:38:47 2010
 * 
 * @brief  Context to use ASP Programs
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "DLV_ASP_ContextAtom.h"
#include "Timing.h"

#include "dlvhex/DLVProcess.h"
#include "dlvhex/AtomSet.h"
#include "dlvhex/Program.h"
#include "dlvhex/HexParserDriver.h"
#include "dlvhex/ASPSolver.h"
#include "dlvhex/TextOutputBuilder.h"

namespace dlvhex {
  namespace mcsdiagexpl {

using namespace std;

void printSet (std::string s) {
  std::cout << s << std::endl;
}

void
DLV_ASP_ContextAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
  std::set<std::string> oset,aset,bset, aointerset, ominusaset;
  set<string> interset, accset;

  const std::string param = query.getInputTuple()[4].getUnquotedString();

  convertQueryToStringSets(query,aset,bset,oset);

  #ifdef DEBUG
       std::cout << "===========================================" << std::endl;
       std::cout << param << std::endl;
       std::cout << "aset: " << std::endl;
       for_each(aset.begin(),aset.end(),printSet);
       std::cout << "oset: " << std::endl;
       for_each(oset.begin(),oset.end(),printSet);
       std::cout << "--------------------------------------------" << std::endl;
  #endif

  if((Timing::getInstance())->isActive()) {
	(Timing::getInstance())->start(context_id);
  }

  /////////////////////////////////////////////////////////////////
  //
  // Parsing Programm given as param into idb and edb
  //
  /////////////////////////////////////////////////////////////////

  //HexParserDriver driver;
  HexParserDriver driver;
  Program idb;
  /// stores the facts of the program
  AtomSet edb;
  driver.parse(param, idb, edb);

  /////////////////////////////////////////////////////////////////
  //
  // add additional rules to the program
  //
  /////////////////////////////////////////////////////////////////

  // add Atomsets b<i> as facts to program
  for (set<string>::iterator inputit = bset.begin(); inputit != bset.end(); ++inputit) {
    //*inputit
    #ifdef DEBUG
      cout << "added input belief: " << *inputit << endl;
    #endif
    edb.insert(AtomPtr(new Atom(Tuple(1, Term(*inputit)))));
  }

  // Rules of Programm
  RuleHead_t h;
  RuleBody_t b;
  h.clear();

  // add the intersection of A and O as Constraint ":- not x."
  std::insert_iterator<std::set<std::string> > aointer_it(aointerset, aointerset.begin());
  set_intersection(aset.begin(), aset.end(), oset.begin(), oset.end(), aointer_it);
  for (set<string>::iterator interit = aointerset.begin(); interit != aointerset.end(); ++interit) {
    b.clear();
    b.insert(new Literal(AtomPtr(new Atom(*interit)), true));
    #ifdef DEBUG
      cout << "added inter Rule: :- not " << *interit << endl;
    #endif
    Rule *r = new Rule(h,b);
    idb.addRule(r);
  }

  // add the difference of O and A as Constraint ":- x."
  std::insert_iterator<std::set<std::string> > ominusaset_it(ominusaset, ominusaset.begin());
  set_difference(oset.begin(), oset.end(), aset.begin(), aset.end(), ominusaset_it);
  for (set<string>::iterator aodiffit = ominusaset.begin(); aodiffit != ominusaset.end(); ++aodiffit) {
    b.clear();
    b.insert(new Literal(AtomPtr(new Atom(*aodiffit)), false));
    #ifdef DEBUG
      cout << "added diff set Rule: :- " << *aodiffit << endl;
    #endif
    idb.addRule(new Rule(h,b));
  }

  /////////////////////////////////////////////////////////////////
  //
  // Solve Program
  //
  /////////////////////////////////////////////////////////////////
  #ifdef DEBUG
    cout << "Start solving dlv program: " << endl;
    const Rule *r;
    int i=0;
    for (Program::const_iterator progit = idb.begin(); progit != idb.end(); ++i, ++progit) {
      r=*(progit);
      cout << *r;
    }

    //cout << (*edb).getArgument(1).getSring();
    for (AtomSet::const_iterator ai = edb.begin(); ai != edb.end(); ++ai) {
      cout << *ai << endl;
    }
    cout << "solve ==========================" << endl;
  #endif

  std::vector<AtomSet> answersets;
  std::vector<AtomSet>::const_iterator as;
  {
    typedef ASPSolverManager::SoftwareConfiguration<ASPSolver::DLVSoftware> DLVConfiguration;
    DLVConfiguration dlv;
    dlv.options.includeFacts = true;
    ASPSolverManager::Instance().solve(dlv, idb, edb, answersets);
  }

  if((Timing::getInstance())->isActive()) {
	(Timing::getInstance())->stop(context_id);
  }

  #ifdef DEBUG
       ResultContainer* result = new ResultContainer();
   
       for (as = answersets.begin(); as!=answersets.end(); ++as) {
         result->addSet(*as);
       }
   
       OutputBuilder *outputbuilder = new TextOutputBuilder();
       result->print(std::cout, outputbuilder);
   
       cout << "-------------------------------------------" << endl;

       cout << "are there Answersets?????? " << endl;
       cout << "Answerset size: " << answersets.size() << endl;
  #endif

  if (answersets.size() > 0) {
    Tuple out;
    answer.addTuple(out);
  }
}

  } // namespace mcsdiagexpl
} // namespace dlvhex
