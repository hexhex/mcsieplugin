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
 * @file   ExplanationPrintVisitor.cpp
 * @author Gerald Weidinger
 * @date   Sun Jan 24 13:43:34 2010
 * 
 * @brief  PrintVisitor to go throught the Answersets and write as Equilibria when compoverexplanations is set
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#include "Global.h"
#endif /* HAVE_CONFIG_H */

#include "ExplanationPrintVisitor.h"

#include "dlvhex/AtomSet.h"
#include <iostream>
#include <sstream>
#include <list>

//#define DEBUG

namespace dlvhex {
  namespace mcsdiagexpl {
////////////////////////////////////////////////////////////////////////////
// 
//	PrintVisitorMethods
//
////////////////////////////////////////////////////////////////////////////
ExplanationPrintVisitor::ExplanationPrintVisitor(std::ostream& s)
: RawPrintVisitor(s)
{ }


void
ExplanationPrintVisitor::visit(const AtomSet* const as)
{
  // diagnosis output
  //typedef std::map<std::string, int> DiagMap;
  std::map<int, std::string> cmap;
  std::multimap<int,std::string> outlist; 
  std::string pred;
  int id=0;

  #ifdef DEBUG
    std::cerr << "Answerset: ";
		::dlvhex::RawPrintVisitor dbgVisitor(std::cerr);
		as->accept(dbgVisitor);
		std::cerr << std::endl;
    //stream << "D1 size: " << d1.size() << "  / D2 size: " << d2.size() << " / normal: " << normal.size() << std::endl;
  #endif

  //stream << '(';

	//std::stringstream e1;
	//std::stringstream e2;

	std::list<std::string> e1;
	std::list<std::string> e2;

  if (!as->empty()) {
    for (AtomSet::atomset_t::const_iterator a = as->atoms.begin(); a != as->atoms.end(); ++a) {
	// get predicate (we are interested in o<i> a<i> d1 d2)
	std::string pred;
	{
		std::stringstream s; s << (*a)->getPredicate();
		pred = s.str();
	}

	if (pred == "e1"){
		std::stringstream k; 
		k << (*a)->getArguments();
		e1.push_back(k.str());
	}
	if (pred == "e2"){
		std::stringstream k; 
		k << (*a)->getArguments();
		e2.push_back(k.str());
	}
     }

	// Ausgabe des Explanation Rewriters

	e1.sort();
	e2.sort();

	if ((Global::getInstance())->isminExp()){
		std::cout << "Em: ";
	}else{
		std::cout << "E: ";
	}

	std::cout << "({";
	if (!(e1.empty())){
		std::cout << e1.front();
		e1.pop_front();
	}
	while (!(e1.empty()))
  	{
    		std::cout << "," << e1.front();
    		e1.pop_front();
  	}
	std::cout << "},{";
	if (!(e2.empty())){
		std::cout << e2.front();
		e2.pop_front();
	}
	while (!(e2.empty()))
  	{
    		std::cout << "," << e2.front();
    		e2.pop_front();
  	}
	std::cout << "})" << std::endl << std::endl;




  } // if empty
}//ExplanationPrintVisitor::visit(AtomSet* const as)


}//namespace mcsdiagexpl
}//namespace dlvhex
// vim:ts=8:
