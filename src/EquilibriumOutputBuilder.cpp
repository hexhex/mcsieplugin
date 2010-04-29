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
 * @file   EquilibriumOutputBuilder.cpp
 * @author Markus Boegl
 * @date   Sun Jan 24 13:40:01 2010
 * 
 * @brief  OutputBuilder to write the Answersets as Equilibria
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "EquilibriumOutputBuilder.h"
#include "dlvhex/globals.h"
#include "dlvhex/ResultContainer.h"
#include "EquilibriumPrintVisitor.h"
#include "DiagnosisPrintVisitor.h"
#include "Timing.h"
#include "Global.h"
#include "dlvhex/DLVProcess.h"
#include "dlvhex/AtomSet.h"
#include "dlvhex/Program.h"
#include "dlvhex/HexParserDriver.h"
#include "dlvhex/ASPSolver.h"
#include "dlvhex/TextOutputBuilder.h"

#include <iostream>
#include <sstream>
#include <string>

//#define DEBUG

namespace dlvhex {
  namespace mcsdiagexpl {


EquilibriumOutputBuilder::EquilibriumOutputBuilder()
{ }


EquilibriumOutputBuilder::~EquilibriumOutputBuilder()
{ }

bool same_AtomSet (boost::tuple<AtomSet,AtomSet,AnswerSetPtr> first, boost::tuple<AtomSet,AtomSet,AnswerSetPtr> second)
{ 
	return ( (first.get<0>() == second.get<0>()) && (first.get<1>() == second.get<1>())); 
}

bool
EquilibriumOutputBuilder::checkAddMinimalResult(ResultList& mrl, AtomSet& d1, AtomSet& d2) {
  bool minimal = false;
  bool skipIt = false;
  ResultList::iterator mit = mrl.begin();
  while(mit != mrl.end()) {
      #ifdef DEBUG
	      RawPrintVisitor rpv(std::cout);
	      std::cout << "   comparing with minimal result ";
	      mit->get<0>().accept(rpv);
	      std::cout << "/";
	      mit->get<1>().accept(rpv);
      #endif

      if( d1.difference(mit->get<0>()).empty()
	  && d2.difference(mit->get<1>()).empty() ) {
	// d1 is contained in the tuples first parameter
	// and d2 is contained in the tuples second parameter
	minimal = true;
	if( mit == mrl.begin() ) {
	  mrl.erase(mit);
	  mit = mrl.begin();
	} else {
	  ResultList::iterator dit = mit;
	  mit++;
	  mrl.erase(dit);
	}
      } else if( mit->get<0>().difference(d1).empty()
  	&& mit->get<1>().difference(d2).empty() ) {
	// the tuples first parameter is contained in d1
	// and the tuples second parameter is contained in d2
	skipIt = true;
	mit++;
      }
      else {
	mit++;
      }
      #ifdef DEBUG
	      std::cout << " skipIt=" << skipIt << " minimal=" << minimal << std::endl;
      #endif
      //assert( (mit->get<0>() == d1 && mit->get<1>() == d2) || "this should not happen");
  } // END while mit != minimalResults.end()
  // we cannot have a minimal answer set which should be skipped
  assert(!(minimal && skipIt));
  if( !skipIt ) {
      return true;
  }
  return false;
}

std::vector<AtomSet> 
EquilibriumOutputBuilder::getExplaination(ResultList& minRes) {
  std::stringstream ss;
  DLVProcess dlv;
  dlv.addOption("-facts");
  //dlv.addOption("-filter=e1,e2");
  std::vector<AtomSet> as;
  HexParserDriver driver;
  Program prog;
  AtomSet asfact;
  AtomSet d1,d2,normal;
  Term e1 = Term("e1");
  Term e2 = Term("e2");
  Term rule = Term("rule");

  ss << "e1(R) v ne1(R) :- rule(R)." << std::endl;
  ss << "e2(R) v ne2(R) :- rule(R)." << std::endl;

  std::auto_ptr<BaseASPSolver> solver(dlv.createSolver());
  std::stringstream rulestream, guessstream;
  for(ResultList::const_iterator rit = minRes.begin(); rit != minRes.end(); ++rit) {
	d1 = rit->get<0>();
	d2 = rit->get<1>();
	for (AtomSet::const_iterator asit = d1.begin(); asit != d1.end(); ++asit) {
	  Atom a1 = *asit;
	  a1.setPredicate(e1);
	  if (asit != d1.begin())
		guessstream << " v ";
	  guessstream << a1;
	  a1.setPredicate(rule);
	  rulestream << a1 << "." << std::endl;
	}
        if( !d1.empty() )
        {
          if( !d2.empty() )
            guessstream << " v " << std::endl;
          else
            guessstream << "." << std::endl;
        }
	for (AtomSet::const_iterator asit = d2.begin(); asit != d2.end(); ++asit) {
	  Atom a2 = *asit;
	  a2.setPredicate(e2);
	  if (asit != d2.begin())
		guessstream << " v ";
	  guessstream << a2;
	  a2.setPredicate(rule);
          rulestream << a2 << "." << std::endl;
	}
        if( !d2.empty() )
          guessstream << "." << std::endl;

	(rit->get<2>())->matchPredicate("normal", normal);
	for (AtomSet::const_iterator asit = normal.begin(); asit != normal.end(); ++asit) {
	  Atom a2 = *asit;
	  a2.setPredicate(rule);
          rulestream << a2 << "." << std::endl;
	}
  }
  ss << rulestream.str() << guessstream.str();
#ifdef DEBUG
  std::cout << "Programm: " << std::endl;
  std::cout << ss.str() << std::endl;
#endif

  driver.parse(ss, prog, asfact);
  solver->solve(prog, asfact, as);

#ifdef DEBUG
    std::cout << "Start solving dlv program: " << std::endl;
    const Rule *r;
    int i=0;
    for (Program::const_iterator progit = prog.begin(); progit != prog.end(); ++i, ++progit) {
      r=*(progit);
      std::cout << *r;
    }

    //cout << (*edb).getArgument(1).getSring();
    for (AtomSet::const_iterator ai = asfact.begin(); ai != asfact.end(); ++ai) {
      std::cout << *ai << std::endl;
    }
    std::cout << "solve ==========================" << std::endl;

  if (as.size() > 0) {
       std::cout << "there are answersets" << std::endl;
       ResultContainer* result = new ResultContainer();
   
       for (std::vector<AtomSet>::const_iterator asit = as.begin(); asit!=as.end(); ++asit) {
         result->addSet(*asit);
       }
   
       OutputBuilder *outputbuilder = new TextOutputBuilder();
       result->print(std::cout, outputbuilder);
  }
  #endif
  return as;
}

void
EquilibriumOutputBuilder::buildResult(std::ostream& stream, const ResultContainer& facts)
{
  if((Timing::getInstance())->isActive()) {
	(Timing::getInstance())->end();
  }

  ResultList minimalResults, minimalExpl, diagnose;
  const ResultContainer::result_t& results = facts.getAnswerSets();

  if (!Globals::Instance()->getOption("Silent"))
    {
      stream << std::endl;
    }

  #ifdef DEBUG
	stream << "result size: " << results.size() << std::endl;
  #endif

  if (!results.empty()) {
	for (ResultContainer::result_t::const_iterator rit = results.begin(); rit != results.end(); ++rit) {
		AtomSet d1, d2, normal;
		(*rit)->matchPredicate("d1", d1);
		(*rit)->matchPredicate("d2", d2);
		(*rit)->matchPredicate("normal", normal);

		if (!(Global::getInstance())->isSet()) {
			// Only print equilibria
			EquilibriumPrintVisitor epv(stream);
			//if ((d1.size() == 0) && (d2.size() == 0) && (normal.size() > 0)) {
			stream << "EQ:";
			(*rit)->accept(epv);
			stream << std::endl;
			if (!Globals::Instance()->getOption("Silent"))
				stream << std::endl;
		} else {
		////////////////////////
		//  --explain is set  //
		////////////////////////
		  if ((Global::getInstance())->isDiag()) {
			if (!(Global::getInstance())->isnoprintopeq()) {
			  // print diagnosis and equilibria
			  stream << "D:";
			  if (!(Global::getInstance())->isnoprintopeq()) {
			    // print diagnosis and equilibria
			    stream << "EQ:";
			  }

			  DiagnosisPrintVisitor dpv(stream);
			  (*rit)->accept(dpv);

			  EquilibriumPrintVisitor epv(stream);
			  stream << ":";
			  (*rit)->accept(epv);
			  stream << std::endl;
			  if (!Globals::Instance()->getOption("Silent"))
				stream << std::endl;
			} else {
			  ///////////////////////////////////////////////////////////////
			  //  For Printing only Diagnosis without Equilibria we filter //
			  //  out duplicate Diagnosis, for that we use the             //
			  //  minimalResults List and filter before printing           //
			  ///////////////////////////////////////////////////////////////
			  diagnose.push_back(boost::make_tuple(d1,d2,*rit));
			}
		  } // end if Diagnose
		  if ((Global::getInstance())->isminDiag()) {
		    if (checkAddMinimalResult(minimalResults,d1,d2))
				minimalResults.push_back(boost::make_tuple(d1,d2,*rit));
		  } // end if Minimal Diagnose
		  if (((Global::getInstance())->isExp() || (Global::getInstance())->isminExp()) && !(Global::getInstance())->isminDiag()) {
		    if (checkAddMinimalResult(minimalResults,d1,d2))
				minimalResults.push_back(boost::make_tuple(d1,d2,*rit));
		  } // end if Explanation or minimal Explanation
		} // end else --explain is set
	} // end for over results

	if ((Global::getInstance())->isExp() || (Global::getInstance())->isminExp()) {
	///////////////////////////////////
	//  get Explanations out of      //
	//  minimal Diagnosis            //
	///////////////////////////////////
	  std::vector<AtomSet> expl = getExplaination(minimalResults);
	  if (expl.size() > 0) {
	    ResultContainer* explrc = new ResultContainer();
	    for (std::vector<AtomSet>::const_iterator asit = expl.begin(); asit!=expl.end(); ++asit) {
		explrc->addSet(*asit);
	    }//end for
	    const ResultContainer::result_t& explres = explrc->getAnswerSets();
	    for (ResultContainer::result_t::const_iterator rit = explres.begin(); rit != explres.end(); ++rit) {
		AtomSet e1,e2;
		(*rit)->matchPredicate("e1", e1);
		(*rit)->matchPredicate("e2", e2);
	        if ((Global::getInstance())->isminExp()) {
		  if (checkAddMinimalResult(minimalExpl,e1,e2)) {
			minimalExpl.push_back(boost::make_tuple(e1,e2,*rit));
		  }//end if checkAddMinimalResult
	        }// if isminExp
		if ((Global::getInstance())->isExp()) {
			stream << "E:";
			DiagnosisPrintVisitor dpv(stream);
			(*rit)->accept(dpv);
			stream << std::endl;
			if (!Globals::Instance()->getOption("Silent")) {
				stream << std::endl;
			}
		}// if isExp
	    }//end for ResultContainer
	    if ((Global::getInstance())->isminExp()) {
		for(ResultList::const_iterator rit = minimalExpl.begin(); rit != minimalExpl.end(); ++rit) {
		  stream << "Em:";
		  DiagnosisPrintVisitor dpv(stream);
		  rit->get<2>()->accept(dpv);
		  stream << std::endl;
		  if (!Globals::Instance()->getOption("Silent")) {
			stream << std::endl;
		  }
		} //end for
	    }// end if isminExp
	  }//end if expl.size() > 0 
	}

	if ((Global::getInstance())->isminDiag()) {
	///////////////////////////////////
	//  Printing minimal diagnosis   //
	//  with or without equilibria   //
	///////////////////////////////////
	  for(ResultList::const_iterator rit = minimalResults.begin(); rit != minimalResults.end(); ++rit) {
		stream << "Dm:";
		if (!(Global::getInstance())->isnoprintopeq()) {
		// print diagnosis and equilibria
			stream << "EQ:";
		}

		DiagnosisPrintVisitor dpv(stream);
		rit->get<2>()->accept(dpv);

		if (!(Global::getInstance())->isnoprintopeq()) {
		// print diagnosis and equilibria
			EquilibriumPrintVisitor epv(stream);
			stream << ":";
			rit->get<2>()->accept(epv);
		}
		stream << std::endl;

		if (!Globals::Instance()->getOption("Silent")) {
			stream << std::endl;
		}
	    } //end for
	///////////////////////////////////
	//  E N D                        //
	//  Printing minimal diagnosis   //
	//  with or without equilibria   //
	///////////////////////////////////
	} 
	if ((Global::getInstance())->isDiag() && (Global::getInstance())->isnoprintopeq()) {
	/////////////////////////////////////////////
	//  Printing diagnosis without equilibria  //
	//  for that we erase duplicates           //
	/////////////////////////////////////////////
	    diagnose.sort();
	    diagnose.unique(same_AtomSet);
	    for(ResultList::const_iterator rit = diagnose.begin(); rit != diagnose.end(); ++rit) {
		stream << "D:";
		DiagnosisPrintVisitor dpv(stream);
		rit->get<2>()->accept(dpv);
		stream << std::endl;
		if (!Globals::Instance()->getOption("Silent")) {
			stream << std::endl;
		}
	    } // end for iterate minimalResults
	} // END else if Printing diagnosis without equilibria
  } // if result !emty

  if((Timing::getInstance())->isActive()) {
	(Timing::getInstance())->stopPostProc();
	stream << std::endl;
	stream << *Timing::getInstance();
  }

  if (results.empty())
    return;
}

}//namespace mcsdiagexpl
}//namespace dlvhex
