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
 * @file   	BridgeRule.cpp
 * @author 	Markus Boegl
 * @author 	Gerald Weidinger
 * @date   	Sun Feb 24 13:31:57 2011
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

  } // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
