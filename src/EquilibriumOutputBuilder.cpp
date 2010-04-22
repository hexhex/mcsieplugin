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
  DLVProcess dlv;
  dlv.addOption("-facts");
  std::vector<AtomSet> as;
  AtomSet d1,d2,normal;
  Term e1 = Term("e1");
  Term e2 = Term("e2");
  Term rule = Term("rule");
  // Rules of Programm
  RuleHead_t h;
  RuleBody_t b;
  Program idb;
  /// stores the facts of the program
  AtomSet edb;
  Rule *r_guess = new Rule(h,b);
  r_guess->addHead(AtomPtr(new Atom(Tuple(1, Term("e1(R)")))));
  r_guess->addHead(AtomPtr(new Atom(Tuple(1, Term("ne1(R)")))));
  r_guess->addBody(new Literal(AtomPtr(new Atom("rule(R)")), false));
// e1(R) v ne1(R) :- rule(R).
// e2(R) v ne2(R) :- rule(R).
  idb.addRule(r_guess);

  r_guess = new Rule(h,b);
  r_guess->addHead(AtomPtr(new Atom(Tuple(1, Term("e2(R)")))));
  r_guess->addHead(AtomPtr(new Atom(Tuple(1, Term("ne2(R)")))));
  r_guess->addBody(new Literal(AtomPtr(new Atom("rule(R)")), false));
  idb.addRule(r_guess);

  std::auto_ptr<BaseASPSolver> solver(dlv.createSolver());
  h.clear();
  b.clear();
  for(ResultList::const_iterator rit = minRes.begin(); rit != minRes.end(); ++rit) {
	h.clear();
	Rule *r = new Rule(h,b);
	//(rit->get<0>()).matchPredicate("d1",d1);
	d1 = rit->get<0>();
	for (AtomSet::const_iterator asit = d1.begin(); asit != d1.end(); ++asit) {
	  Atom a1 = *asit;
	  a1.setPredicate(e1);
	  r->addHead(AtomPtr(new Atom(a1)));
	  a1.setPredicate(rule);
	  edb.insert(AtomPtr(new Atom(a1)));
	}
	d2 = rit->get<1>();
	for (AtomSet::const_iterator asit = d2.begin(); asit != d2.end(); ++asit) {
	  Atom a2 = *asit;
	  a2.setPredicate(e2);
	  r->addHead(AtomPtr(new Atom(a2)));
	  a2.setPredicate(rule);
	  edb.insert(AtomPtr(new Atom(a2)));
	}
	idb.addRule(r);
	(rit->get<2>())->matchPredicate("normal", normal);
	for (AtomSet::const_iterator asit = normal.begin(); asit != normal.end(); ++asit) {
	  Atom a2 = *asit;
	  a2.setPredicate(rule);
	  edb.insert(AtomPtr(new Atom(a2)));
	}
  }
//#ifdef DEBUG
    std::cout << "Start solving dlv program: " << std::endl;
    const Rule *r;
    int i=0;
    for (Program::const_iterator progit = idb.begin(); progit != idb.end(); ++i, ++progit) {
      r=*(progit);
      std::cout << *r;
    }

    //cout << (*edb).getArgument(1).getSring();
    for (AtomSet::const_iterator ai = edb.begin(); ai != edb.end(); ++ai) {
      std::cout << *ai << std::endl;
    }
    std::cout << "solve ==========================" << std::endl;
//#endif
  //solver->solve(idb, edb, as);
  if (as.size() > 0)
	std::cout << "there are ansersets";
  return as;
}

void
EquilibriumOutputBuilder::buildResult(std::ostream& stream, const ResultContainer& facts)
{
  if((Timing::getInstance())->isActive()) {
	(Timing::getInstance())->end();
  }

  bool lb = false; //line break
  ResultList minimalResults;
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

		if (!(Global::getInstance())->isDiag() && !(Global::getInstance())->isExp()) {
			// Only print equilibria
			EquilibriumPrintVisitor epv(stream);
			//if ((d1.size() == 0) && (d2.size() == 0) && (normal.size() > 0)) {
				stream << "EQ: ";
				(*rit)->accept(epv);
				lb = true;
			//}
		} else if ((Global::getInstance())->isDiag()) {
			// Print Diagnosis
			if ((Global::getInstance())->isMin()) {
			///////////////////////////////////
			//  calculate minimal diagnosis  //
			//  NO direct printing           //
			///////////////////////////////////
				#ifdef DEBUG
				    RawPrintVisitor rpv(stream);
				    stream << " looking at result set ";
				    //(*rit)->accept(rpv);
				    d1.accept(rpv);
				    stream << "/";
				    d2.accept(rpv);
				    stream << std::endl;
				#endif
				if (checkAddMinimalResult(minimalResults,d1,d2)) {
					minimalResults.push_back(boost::make_tuple(d1,d2,*rit));
			      #ifdef DEBUG
			      	stream << " -> adding resultset to minimal ones: ";
			        RawPrintVisitor rpv(stream);
			        (*rit)->accept(rpv);
			        stream << std::endl;
			      #endif
				}
				// call add
			///////////////////////////////////
			//   E N D   Minimal Diagnosis   //
			///////////////////////////////////
			} else {
			///////////////////////////////////
			//  NO minimal diagnosis         //
			///////////////////////////////////
			    if (!(Global::getInstance())->isnoprintopeq()) {
			    // print diagnosis and equilibria
				stream << "D:";
				if (!(Global::getInstance())->isnoprintopeq()) {
				// print diagnosis and equilibria
					stream << "EQ: ";
				} else {
				// print only diagnosis
					stream << " ";
				}

				DiagnosisPrintVisitor dpv(stream);
				(*rit)->accept(dpv);

				
				EquilibriumPrintVisitor epv(stream);
				stream << ":";
				(*rit)->accept(epv);
				lb = true;
			    } else {
			    ///////////////////////////////////////////////////////////////
			    //  For Printing only Diagnosis without Equilibria we filter //
			    //  out duplicate Diagnosis, for that we use the             //
			    //  minimalResults List and filter before printing           //
			    ///////////////////////////////////////////////////////////////
				minimalResults.push_back(boost::make_tuple(d1,d2,*rit));
			    }
			} //end else not Minimal Diagnosis
		} else if ((Global::getInstance())->isExp()) {
			// for calculate Explanation
			// first calculate Minimal Diagnosis
				#ifdef DEBUG
				    RawPrintVisitor rpv(stream);
				    stream << " looking at result set ";
				    //(*rit)->accept(rpv);
				    d1.accept(rpv);
				    stream << "/";
				    d2.accept(rpv);
				    stream << std::endl;
				#endif
			if (checkAddMinimalResult(minimalResults,d1,d2)) {
				minimalResults.push_back(boost::make_tuple(d1,d2,*rit));

			      #ifdef DEBUG
			      	stream << " -> adding resultset to minimal ones: ";
			        RawPrintVisitor rpv(stream);
			        (*rit)->accept(rpv);
			        stream << std::endl;
			      #endif
			}
		}
		if (lb) stream << std::endl;
		if (!Globals::Instance()->getOption("Silent")) {
			if (lb) stream << std::endl;
		}
		lb = false;
	} // end for over results

	if ((Global::getInstance())->isExp()) {
	///////////////////////////////////
	//  get Explanations out of      //
	//  minimal Diagnosis            //
	///////////////////////////////////
	  std::vector<AtomSet> expl = getExplaination(minimalResults);

#if 0
	  if ((Global::getInstance())->isMin()) {
		AtomSet min_expl;
	  	for(ResultList::const_iterator rit = minimalResults.begin(); rit != minimalResults.end(); ++rit) {
			min_expl.insert(rit->get<0>());
			min_expl.insert(rit->get<1>());
		}
		DiagnosisPrintVisitor dpv(stream);
		stream << "Em: ";
		min_expl.accept(dpv);
		stream << std::endl;
	  }
#endif
	}

	if ((Global::getInstance())->isDiag() && (Global::getInstance())->isMin()) {
	///////////////////////////////////
	//  Printing minimal diagnosis   //
	//  with or without equilibria   //
	///////////////////////////////////
	  for(ResultList::const_iterator rit = minimalResults.begin(); rit != minimalResults.end(); ++rit) {
		stream << "Dm:";
		if (!(Global::getInstance())->isnoprintopeq()) {
		// print diagnosis and equilibria
			stream << "EQ: ";
		} else {
		// print only diagnosis
			stream << " ";
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
	} else if ((Global::getInstance())->isDiag() && !(Global::getInstance())->isMin() && (Global::getInstance())->isnoprintopeq()) {
	/////////////////////////////////////////////
	//  Printing diagnosis without equilibria  //
	//  for that we erase duplicates           //
	/////////////////////////////////////////////
	    minimalResults.sort();
	    minimalResults.unique(same_AtomSet);
	    for(ResultList::const_iterator rit = minimalResults.begin(); rit != minimalResults.end(); ++rit) {
		stream << "D: ";
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
