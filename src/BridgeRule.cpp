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
 * @file   BridgeRule.cpp
 * @author Markus Boegl
 * @date   Sun Jan 24 13:31:57 2010
 * 
 * @brief  BridgeRule element for Parsing the Input file
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "BridgeRule.h"
#include "Global.h"

#include <ostream>
#include <list>


#include <iostream>
#include <sstream>


using std::cout;


namespace dlvhex {
  namespace mcsdiagexpl {

  BridgeRule::BridgeRule() {
     fact = false;
   }

  BridgeRule::BridgeRule(bool f) {
     fact = f;
   }

   void
   BridgeRule::setHeadRule(std::string rid, int cid, std::string f) {
     ruleid = rid;
     head = BridgeRuleEntry(cid,f);
   } // end of BridgeRule::setHeadRule

   void
   BridgeRule::addBodyRule(int id, std::string f, bool n){
     BridgeRuleEntry elem = BridgeRuleEntry(id,f,n);
     body.push_back(elem);
   } // end of BridgeRule::addBodyRule



void 
   BridgeRule::writeProgramEx(std::ostream& o) {
     // write bridgerule in asp form
     std::list<int> ilist;


     std::stringstream iny;
     iny << "in_" << head.ContextID() << "(" << head.Fact() << ") :- r1(" << ruleid << ")";
     for (std::vector<BridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
       const BridgeRuleEntry& elem = *it;
       iny << ", pres_" << elem.ContextID() << "(" << elem.Fact() << ")";	
       //std::cout << "pres_" << elem.ContextID() << "(" << elem.Fact() << ") v abs_" << elem.ContextID() << "(" << elem.Fact() << ")." << std::endl;
	// 7.) i.e. OUTi, so Vo e OUTi add out_i(o)	
	//std::cout << "out_" << elem.ContextID() << "(" << elem.Fact() << ")." << std::endl;
	// 10.) saturate on spoil	
	//std::cout << "pres_" << elem.ContextID() << "(" << elem.Fact() << ") :- spoil." << std::endl;
	//std::cout << "abs_" << elem.ContextID() << "(" << elem.Fact() << ") :- spoil." << std::endl;
	//9.) spoil if our guesses are wrong by themselves.
	//std::cout << "spoil :- pres_" << elem.ContextID() << "(" << elem.Fact() << "), " << "abs_" << elem.ContextID() << "(" << elem.Fact() << ")." << std::endl;

	o << "pres_" << elem.ContextID() << "(" << elem.Fact() << ") v abs_" << elem.ContextID() << "(" << elem.Fact() << ")." << std::endl;
	// 7.) i.e. OUTi, so Vo e OUTi add out_i(o)	
	o << "out_" << elem.ContextID() << "(" << elem.Fact() << ")." << std::endl;
	// 10.) saturate on spoil	
	o << "pres_" << elem.ContextID() << "(" << elem.Fact() << ") :- spoil." << std::endl;
	o << "abs_" << elem.ContextID() << "(" << elem.Fact() << ") :- spoil." << std::endl;
	//9.) spoil if our guesses are wrong by themselves.
	o << "spoil :- pres_" << elem.ContextID() << "(" << elem.Fact() << "), " << "abs_" << elem.ContextID() << "(" << elem.Fact() << ")." << std::endl;

     }
	iny << ".";
	// derive applicable rule heads
	//std::cout << iny.str() << std::endl;
	// derive heads of unconditional rules.
	//std::cout << "in_" << head.ContextID() << "(" << head.Fact() << ") :- r2(" << ruleid << ")." << std::endl;
	// 10.) saturate on spoil
	//std::cout << "in_" << head.ContextID() << "(" << head.Fact() << ") :- spoil." << std::endl;
	//9.) spoil if our guesses are wrong by themselves.
	//std::cout << "spoil :- r1(" << ruleid << "), " << "nr1(" << ruleid << ")." << std::endl;
	//std::cout << "spoil :- r2(" << ruleid << "), " << "nr2(" << ruleid << ")." << std::endl;
	
	//guess an explanation candidate.
	//std::cout << "e1(" << ruleid << ") v ne1(" << ruleid << ")." << std::endl;
	//std::cout << "e2(" << ruleid << ") v ne2(" << ruleid << ")." << std::endl;
	//std::cout << ":- e1(" << ruleid << "), ne1(" << ruleid << ")." << std::endl;
	//std::cout << ":- e2(" << ruleid << "), ne2(" << ruleid << ")." << std::endl;;

	// 10.) saturate on spoil	
	//std::cout << "r1(" << ruleid << ") :- spoil." << std::endl;
	//std::cout << "r2(" << ruleid << ") :- spoil." << std::endl;
	//std::cout << "nr1(" << ruleid << ") :- spoil." << std::endl;
	//std::cout << "nr2(" << ruleid << ") :- spoil." << std::endl;



	// derive applicable rule heads
	o << iny.str() << std::endl;
	// derive heads of unconditional rules.
	o << "in_" << head.ContextID() << "(" << head.Fact() << ") :- r2(" << ruleid << ")." << std::endl;
	// 10.) saturate on spoil
	o << "in_" << head.ContextID() << "(" << head.Fact() << ") :- spoil." << std::endl;
	//9.) spoil if our guesses are wrong by themselves.
	o << "spoil :- r1(" << ruleid << "), " << "nr1(" << ruleid << ")." << std::endl;
	o << "spoil :- r2(" << ruleid << "), " << "nr2(" << ruleid << ")." << std::endl;
	
	//guess an explanation candidate.
	o << "e1(" << ruleid << ") v ne1(" << ruleid << ")." << std::endl;
	o << "e2(" << ruleid << ") v ne2(" << ruleid << ")." << std::endl;
	o << ":- e1(" << ruleid << "), ne1(" << ruleid << ")." << std::endl;
	o << ":- e2(" << ruleid << "), ne2(" << ruleid << ")." << std::endl;;

	// 10.) saturate on spoil	
	o << "r1(" << ruleid << ") :- spoil." << std::endl;
	o << "r2(" << ruleid << ") :- spoil." << std::endl;
	o << "nr1(" << ruleid << ") :- spoil." << std::endl;
	o << "nr2(" << ruleid << ") :- spoil." << std::endl;

     }



  } // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
