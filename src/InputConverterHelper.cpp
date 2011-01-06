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
 * @file   InputConverterHelper.cpp
 * @author Gerald Weidinger (Refactored)
 * @date   Sun Dez 28 13:34:29 2010
 * 
 * @brief  Contains Methods which are used for both classes: InputConverterExplanations and InputConverterExplanations in order to create the parsetree
 *		and parse the Rules.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "InputConverterHelper.h"
#include "dlvhex/SpiritDebugging.h"
#include "BridgeRuleEntry.h"
#include "Global.h"


#include <iostream>
#include <sstream>

namespace dlvhex {
  namespace mcsdiagexpl {

	InputConverterHelper* InputConverterHelper::ich = NULL;

	InputConverterHelper*
	InputConverterHelper::getInstance() {
		if (ich == NULL) {
		  ich = new InputConverterHelper();
		  //e->init();
		}
		return ich;
		//return NULL;
	}

   void
   InputConverterHelper::convertBridgeRuleElem(node_t& at, std::string& ruleid, int& contextid, std::string& fact) {
        node_t* n = &at;
	node_t::tree_iterator it = at.children.begin();
	node_t& bat = *it;
	//std::cout << "bat children size: " << std::string(bat.value.begin(), bat.value.end()) << std::endl;
	if (bat.value.id() == MCSdescriptionGrammar::RuleID) {
		ruleid = std::string(bat.value.begin(), bat.value.end());
		++it;
		bat = *it;
	} else ruleid = std::string("");
	assert(bat.value.id() == MCSdescriptionGrammar::RuleNum);
        contextid = atoi(std::string(bat.value.begin(), bat.value.end()).c_str());
	++it;
	bat = *it;
	assert(bat.value.id() == MCSdescriptionGrammar::Fact);
        fact = std::string(bat.value.begin(), bat.value.end());
   } // end convertBridgeRuleElem

   void
   InputConverterHelper::convertBridgeRuleFact(node_t& at, BridgeRule& brule) {
     int cid;
     std::string f,rid;
     if (at.value.id() == MCSdescriptionGrammar::RuleHeadElem) {
         #ifdef DEBUG
           printSpiritPT(std::cout, at, "HeadElem");
         #endif
         assert(at.children.size() == 3);
	 convertBridgeRuleElem(at,rid,cid,f);
	 brule.setHeadRule(rid,cid,f);
     }//end if-rule bridgeruleheadelem
   }// End MCSequilibriumConverter::convertBridgeExplanationUnit::getInstance()->Rule()

   void
   InputConverterHelper::convertBridgeRule(node_t& at, BridgeRule& brule) {
     int cid;
     std::string f, rid;
     for (node_t::tree_iterator ait = at.children.begin(); ait != at.children.end(); ++ait) {
       node_t& bat = *ait;
       ////////////////////////////////////////////
       // get the Head of the BridgeRule         //
       ////////////////////////////////////////////
       if (bat.value.id() == MCSdescriptionGrammar::RuleHeadElem) {
         #ifdef DEBUG
           printSpiritPT(std::cout, bat, "HeadElem");
         #endif
         assert(bat.children.size()==3);
	 convertBridgeRuleElem(bat,rid,cid,f);
	 brule.setHeadRule(rid,cid,f);
       }//end if-rule bridgeruleheadelem
       ////////////////////////////////////////////
       // there are more than 1 rule in the body //
       ////////////////////////////////////////////
       if (bat.value.id() == MCSdescriptionGrammar::RuleBody) {
         for (node_t::tree_iterator bit = bat.children.begin(); bit != bat.children.end(); ++bit) {
           node_t& bbeat = *bit;
           if (bbeat.value.id() == MCSdescriptionGrammar::RuleElem) {
             #if 0
               printSpiritPT(std::cout, bbeat, "RuleBodyElem");
             #endif
             assert(bbeat.children.size()==2);
             convertBridgeRuleElem(bbeat,rid,cid,f);
	     brule.addBodyRule(cid,f,false);
           }//end if-rule for RuleElem in BridgeRuleBody
           if (bbeat.value.id() == MCSdescriptionGrammar::NegRuleElem) {
	     #if 0
               printSpiritPT(std::cout, bbeat, "NegatedRuleBodyElem");
	     #endif
             assert(bbeat.children.size()==2);
             convertBridgeRuleElem(bbeat,rid,cid,f);
	     brule.addBodyRule(cid,f,true);
           }//end if-rule for negated RuleElem in BridgeRuleBody
         }// end for-loop over RuleBodyElems
       }//end if-rule RuleBodyElems

       ////////////////////////////////////////////
       // there is only 1 rule in the body       //
       ////////////////////////////////////////////
       if (bat.value.id() == MCSdescriptionGrammar::RuleElem) {
         #if 0
           printSpiritPT(std::cout, bat, "RuleBodyElem");
         #endif
         assert(bat.children.size()==2);
         convertBridgeRuleElem(bat,rid,cid,f);
	 brule.addBodyRule(cid,f,false);
       }//end if-rule for RuleElem in BridgeRuleBody
       if (bat.value.id() == MCSdescriptionGrammar::NegRuleElem) {
	 #if 0
           printSpiritPT(std::cout, bat, "NegatedRuleBodyElem");
	 #endif
         assert(bat.children.size()==2);
         convertBridgeRuleElem(bat,rid,cid,f);
	 brule.addBodyRule(cid,f,true);
       }//end if-rule for negated RuleElem in BridgeRuleBody
     } //end for-loop over bridgerules
   }// End MCSequilibriumConverter::convertBridgeRule()

   void
   InputConverterHelper::convertContext(node_t& at, ParseContext& context) {
     int id;
     std::string extatom;
     std::string param;

     assert(at.children.size() == 3);
     node_t::tree_iterator it = at.children.begin();
     node_t& bat = *it;
     assert(bat.value.id() == MCSdescriptionGrammar::ContextNum);
     id = atoi(std::string(bat.value.begin(), bat.value.end()).c_str());
     ++it;
     bat = *it;
     assert(bat.value.id() == MCSdescriptionGrammar::ExtAtom);
     extatom = std::string(bat.value.begin(), bat.value.end());
     ++it;
     bat = *it;
     assert(bat.value.id() == MCSdescriptionGrammar::Param);
     param = std::string(bat.value.begin(), bat.value.end());
     context = ParseContext(id,extatom,param);
   }// END MCSequilibriumConverter::convertContext

  } // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
