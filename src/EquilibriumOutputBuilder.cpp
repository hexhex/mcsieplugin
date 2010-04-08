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

#include <boost/tuple/tuple.hpp>
#include <iostream>

//#define DEBUG

namespace dlvhex {
  namespace mcsdiagexpl {

EquilibriumOutputBuilder::EquilibriumOutputBuilder()
{ }


EquilibriumOutputBuilder::~EquilibriumOutputBuilder()
{ }


void
EquilibriumOutputBuilder::buildResult(std::ostream& stream, const ResultContainer& facts)
{
  if((Timing::getInstance())->isActive()) {
	(Timing::getInstance())->end();
  }

  bool lb = false; //line break
  typedef std::list< boost::tuple<AtomSet,AtomSet,AnswerSetPtr> > ResultList;
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
			if ((d1.size() == 0) && (d2.size() == 0) && (normal.size() > 0)) {
				stream << "EQ: ";
				(*rit)->accept(epv);
				lb = true;
			}
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

				bool minimal = false;
				bool skipIt = false;
				ResultList::iterator mit = minimalResults.begin();
				while(mit != minimalResults.end()) {
				      #ifdef DEBUG
					      RawPrintVisitor rpv(stream);
					      stream << "   comparing with minimal result ";
					      mit->get<0>().accept(rpv);
					      stream << "/";
					      mit->get<1>().accept(rpv);
				      #endif

				      if( d1.difference(mit->get<0>()).empty()
					  && d2.difference(mit->get<1>()).empty() ) {
					// d1 is contained in the tuples first parameter
					// and d2 is contained in the tuples second parameter
					minimal = true;
					if( mit == minimalResults.begin() ) {
					  minimalResults.erase(mit);
					  mit = minimalResults.begin();
					} else {
					  ResultList::iterator dit = mit;
					  mit++;
					  minimalResults.erase(dit);
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
					      stream << " skipIt=" << skipIt << " minimal=" << minimal << std::endl;
				      #endif
				      //assert( (mit->get<0>() == d1 && mit->get<1>() == d2) || "this should not happen");
				} // END while mit != minimalResults.end()
				// we cannot have a minimal answer set which should be skipped
				assert(!(minimal && skipIt));
				if( !skipIt ) {
				      #ifdef DEBUG
				      	stream << " -> adding resultset to minimal ones: ";
				        RawPrintVisitor rpv(stream);
				        (*rit)->accept(rpv);
				        stream << std::endl;
				      #endif
				      minimalResults.push_back(boost::make_tuple(d1,d2,*rit));
				}
			///////////////////////////////////
			//   E N D   Minimal Diagnosis   //
			///////////////////////////////////
			} else {
			///////////////////////////////////
			//  NO minimal diagnosis         //
			///////////////////////////////////
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

				if (!(Global::getInstance())->isnoprintopeq()) {
				// print diagnosis and equilibria
					EquilibriumPrintVisitor epv(stream);
					stream << ":";
					(*rit)->accept(epv);
				}
				lb = true;
			} //end else not Minimal Diagnosis
		} else if ((Global::getInstance())->isExp()) {
			// Print Explanation
			stream << "E";
			if ((Global::getInstance())->isMin()) {
			//calculate minimal Explanation
				stream << "m";
			}
			stream << ": ";
		}
		if (lb) stream << std::endl;
		if (!Globals::Instance()->getOption("Silent")) {
			if (lb) stream << std::endl;
		}
		lb = false;
	} // end for over results
	if ((Global::getInstance())->isDiag() && (Global::getInstance())->isMin()) {
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
	  } // end for over minimalResults
	} // END Minimal Diagnosis PRINTING
  }

  if((Timing::getInstance())->isActive()) {
	stream << std::endl;
	stream << *Timing::getInstance();
  }

  if (results.empty())
    {
      return;
    }

}

}//namespace mcsdiagexpl
}//namespace dlvhex
