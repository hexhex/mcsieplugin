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

#include <ostream>
#include <list>


namespace dlvhex {
  namespace mcsdiagexpl {

  BridgeRule::BridgeRule() {
     fact = false;
   }

  BridgeRule::BridgeRule(bool f) {
     fact = f;
   }


   BridgeRule::BridgeRule(bool f, std::string i) {
	fact = f;
	id = i;
   }

   void
   BridgeRule::setHeadRule(int id, std::string f) {
     head = BridgeRuleEntry(id,f);
   } // end of BridgeRule::setHeadRule

   void
   BridgeRule::addBodyRule(int id, std::string f, bool n){
     BridgeRuleEntry elem = BridgeRuleEntry(id,f,n);
     body.push_back(elem);
   } // end of BridgeRule::addBodyRule

   void 
   BridgeRule::writeProgram(std::ostream& o) {
     // write bridgerule in asp form
     std::list<int> ilist;


     // output diagnosis disjunction
     o << "normal(" << head.ContextID() << ") v d1(" << head.ContextID() << ") v d2(" << head.ContextID() << ")." << std::endl;

     // output d2 rule
     o << "b" << head << " :- d2(" << head.ContextID() << ")." << std::endl;

     // output d1 rule
     o << "b" << head << " :- not d1(" << head.ContextID() << ")";


     if( fact )
       o << "." << std::endl;
     else { // no fact, so body is emty
       	     o << ", ";
	     //o << "b" << head << " :- ";
	     for (std::vector<BridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
	       BridgeRuleEntry elem = *it;
	       if (elem.Neg())
		 o << "n";
	       o << "a" << elem;
	       if (it+1 != body.end())
		 o << ", ";
	       else
		 o << "." << std::endl;
	     }
	     for (std::vector<BridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
	       BridgeRuleEntry elem = *it;
	       o << "a" << elem << " v na" << elem << "." << std::endl;
	       ilist.push_back(elem.ContextID());
	     }
	     ilist.unique();
	     ilist.sort();
	     for (std::list<int>::iterator it = ilist.begin(); it != ilist.end(); ++it) {
	       o << "o" << *it << "(X) :- a" << *it << "(X)." << std::endl;
	       o << "o" << *it << "(X) :- na" << *it << "(X)." << std::endl;
	     }
     }
   }
  } // namespace mcsdiagexpl
} // namespace dlvhex
