/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2009,2010  Markus Boegl
 * Copyright (C) 2010,2011  Gerald Weidinger
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
 * @file   MinPrintDualConvertFinalCallback.cpp
 * @author Peter Schueller
 * @author Gerald Weidinger
 * 
 * @brief  Final callback for MCSIE (prints minimal notions, converts to dual notion)
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MinPrintDualConvertFinalCallback.h"

#include <cassert>

namespace dlvhex {
namespace mcsdiagexpl {

typedef ASPSolverManager::SoftwareConfigurationPtr ASPSoftwarePtr;

MinPrintDualConvertFinalCallback::
MinPrintDualConvertFinalCallback(ProgramCtxData& pcd, PrintAndAccumulateModelCallback& mcb, ASPSoftwarePtr software):
	pcd(pcd),
  mcb(mcb),
  software(software),
  nprinter(mcb.nprinter),
  eqprinter(mcb.eqprinter)
{
}

DiagRewritingFinalCallback::
DiagRewritingFinalCallback(ProgramCtxData& pcd, PrintAndAccumulateModelCallback& mcb, ASPSoftwarePtr software):
  MinPrintDualConvertFinalCallback(pcd, mcb, software)
{
}

ExplRewritingFinalCallback::
ExplRewritingFinalCallback(ProgramCtxData& pcd, PrintAndAccumulateModelCallback& mcb, ASPSoftwarePtr software):
  MinPrintDualConvertFinalCallback(pcd, mcb, software)
{
}

void DiagRewritingFinalCallback::
operator()()
{
  typedef MinimalNotionCollector::MinimalNotion MinimalNotion;
  typedef std::list<MinimalNotion>::const_iterator MinimalNotionIterator;

  std::ostream& o = std::cout;

  RegistryPtr reg = pcd.reg;

	if( pcd.isminDiag() )
  {
    // print minimal diagnosis notions
    for(MinimalNotionIterator it = pcd.mindcollector->getMinimals().begin();
        it != pcd.mindcollector->getMinimals().end(); ++it)
    {
      if( pcd.isprintOPEQ() )
      {
        for(std::list<InterpretationPtr>::const_iterator itl = it->full.begin();
            itl != it->full.end(); ++itl)
        {
          o << "Dm:EQ:";
          nprinter.print(o, *itl);
          o << ":";
          eqprinter.print(o,*itl);
          o << std::endl;
        }
      }
      else
      {
        o << "Dm:";
        nprinter.print(o, it->full.front());
        o << std::endl;
      }
    }
  }

	if( !pcd.isminExp() && !pcd.isExp() )
    return;

  // else do conversion minimal diagnoses -> explanations
  // (if we need to convert to explanations, we already collected
  // minimal diagnoses during model enumeration!)
  std::string prog;
  {
    std::stringstream ss;
    ss << "e1(R) v ne1(R) :- rule(R)." << std::endl;
    ss << "e2(R) v ne2(R) :- rule(R)." << std::endl;

    // for every bridge rule we create a predicate rule(br).    		
    for(BridgeRuleIterator it = pcd.mcs().rules.begin();
        it != pcd.mcs().rules.end(); ++it)
    {
      ss << "rule(" << it->Id() << ").\n";
    }

    // for each minimal diagnosis
    for(MinimalNotionIterator itn = pcd.mindcollector->getMinimals().begin();
        itn != pcd.mindcollector->getMinimals().end(); ++itn)
    {
      {
        bool first = true;
        Interpretation::TrueBitIterator it, it_end;
        for(boost::tie(it, it_end) = itn->projected1->trueBits();
            it != it_end; ++it)
        {
          const OrdinaryAtom& a = itn->projected1->getAtomToBit(it);
          assert(a.tuple.size() == 2);
          const std::string& ruleid = reg->getTermStringByID(a.tuple[1]);
          if( first ) first = false;
          else ss << " v ";
          ss << "e1(" << ruleid << ")";
        }

        for(boost::tie(it, it_end) = itn->projected2->trueBits();
            it != it_end; ++it)
        {
          const OrdinaryAtom& a = itn->projected2->getAtomToBit(it);
          assert(a.tuple.size() == 2);
          const std::string& ruleid = reg->getTermStringByID(a.tuple[1]);
          if( first ) first = false;
          else ss << " v ";
          ss << "e2(" << ruleid << ")";
        }

        if( first )
        {
          // empty diagnosis -> system is consistent -> make this program inconsistent
          ss << "true. :- true.\n";
        }
        else
        {
          ss << ".\n";
        }
      }
    }

    prog = ss.str();
  }

  DBGLOG(DBG,"conversion from diagnoses to explanations uses program:\n" << prog);

  InputProviderPtr inp(new InputProvider());
  inp->addStringInput(prog,"mcsie_conv_diag_expl");

  ASPSolverManager mgr;
  ASPSolverManager::ResultsPtr results = mgr.solve(*software, *inp, reg);

  // prepare notion printer for explanations
  NotionPrinter eprinter(pcd, pcd.ide1, pcd.ide2, pcd.bremask);

  // retrieve all answer sets
  // and feed them into minimal diagnosis notion collector (unused so far in --iemode=expl)
  AnswerSetPtr as = results->getNextAnswerSet();
  while( !!as )
  {
    DBGLOG(DBG,"Dm->Em converter got answer set " << *as->interpretation);
    if( pcd.isExp() )
    {
      o << "E:";
      eprinter.print(o, as->interpretation);
      o << std::endl;
    }
    if( pcd.isminExp() )
    {
      pcd.minecollector->record(as->interpretation);
    }
    as = results->getNextAnswerSet();
  }

  if( pcd.isminExp() )
  {
    // get minimal notions and print them
    for(std::list<MinimalNotion>::const_iterator it =
          pcd.minecollector->getMinimals().begin();
        it != pcd.minecollector->getMinimals().end(); ++it)
    {
      assert(it->full.size() == 1 && "should only have one answer set for converted notions");
      o << "Em:";
      eprinter.print(o, it->full.front());
      o << std::endl;
    }
  }
}

void ExplRewritingFinalCallback::
operator()()
{
  typedef MinimalNotionCollector::MinimalNotion MinimalNotion;
  typedef std::list<MinimalNotion>::const_iterator MinimalNotionIterator;

  std::ostream& o = std::cout;

  RegistryPtr reg = pcd.reg;

	if( pcd.isminExp() )
  {
    // print minimal explanation notions
    for(MinimalNotionIterator it = pcd.minecollector->getMinimals().begin();
        it != pcd.minecollector->getMinimals().end(); ++it)
    {
      o << "Em:";
      nprinter.print(o, it->full.front());
      o << std::endl;
    }
  }

  assert(!pcd.isDiag() && "convertion from explanation to diagnosis not possible!");

	if( !pcd.isminDiag() )
    return;

  // else do conversion minimal explanations -> minimal diagnoses
  // (if we need to convert to diagnoses, we already collected
  // minimal explanations during model enumeration!)
  std::string prog;
  {
    std::stringstream ss;
    ss << "d1(R) v nd1(R) :- rule(R)." << std::endl;
    ss << "d2(R) v nd2(R) :- rule(R)." << std::endl;
    ss << ":- d1(R), d2(R)." << std::endl; // this is not necessary, but not wrong either
    // (we only use the subset-minimal result of this, which never contains d1 and d2 for a rule)

    // for every bridge rule we create a predicate rule(br).    		
    for(BridgeRuleIterator it = pcd.mcs().rules.begin();
        it != pcd.mcs().rules.end(); ++it)
    {
      ss << "rule(" << it->Id() << ").\n";
    }

    // for each minimal explanation
    for(MinimalNotionIterator itn = pcd.minecollector->getMinimals().begin();
        itn != pcd.minecollector->getMinimals().end(); ++itn)
    {
      {
        bool first = true;
        Interpretation::TrueBitIterator it, it_end;
        for(boost::tie(it, it_end) = itn->projected1->trueBits();
            it != it_end; ++it)
        {
          const OrdinaryAtom& a = itn->projected1->getAtomToBit(it);
          assert(a.tuple.size() == 2);
          const std::string& ruleid = reg->getTermStringByID(a.tuple[1]);
          if( first ) first = false;
          else ss << " v ";
          ss << "d1(" << ruleid << ")";
        }

        for(boost::tie(it, it_end) = itn->projected2->trueBits();
            it != it_end; ++it)
        {
          const OrdinaryAtom& a = itn->projected2->getAtomToBit(it);
          assert(a.tuple.size() == 2);
          const std::string& ruleid = reg->getTermStringByID(a.tuple[1]);
          if( first ) first = false;
          else ss << " v ";
          ss << "d2(" << ruleid << ")";
        }

        if( !first )
        {
          // nonempty explanation -> finish disjunction
          ss << ".\n";
        }
      }
    }

    prog = ss.str();
  }

  DBGLOG(DBG,"conversion from explanations to diagnoses uses program:\n" << prog);

  InputProviderPtr inp(new InputProvider());
  inp->addStringInput(prog,"mcsie_conv_expl_diag");

  ASPSolverManager mgr;
  ASPSolverManager::ResultsPtr results = mgr.solve(*software, *inp, reg);

  // retrieve all answer sets
  // and feed them into minimal diagnosis notion collector (unused so far in --iemode=expl)
  AnswerSetPtr as = results->getNextAnswerSet();
  while( !!as )
  {
    DBGLOG(DBG,"Em->Dm converter got answer set " << *as->interpretation);
    pcd.mindcollector->record(as->interpretation);
    as = results->getNextAnswerSet();
  }

  // get minimal notions and print them
  NotionPrinter dmprinter(pcd, pcd.idd1, pcd.idd2, pcd.brdmask);
  for(std::list<MinimalNotion>::const_iterator it =
        pcd.mindcollector->getMinimals().begin();
      it != pcd.mindcollector->getMinimals().end(); ++it)
  {
    assert(!pcd.isprintOPEQ() && "cannot print output projected equilibria when converting explanations to diagnoses");
    assert(it->full.size() == 1 && "should only have one answer set for converted notions");
    o << "Dm:";
    dmprinter.print(o, it->full.front());
    o << std::endl;
  }
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=2:sw=2:
