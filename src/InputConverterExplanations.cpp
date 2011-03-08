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
 * @file   Converter.cpp
 * @author Gerald Weidinger
 * @date   Sun Jan 24 13:34:29 2010
 * 
 * @brief  Converts the Input file if --compoverex is set
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "InputConverter.h"
#include "dlvhex/SpiritDebugging.h"
#include "BridgeRuleEntry.h"
#include "Global.h"
#include "InputConverterExplanations.h"


#include <iostream>
#include <sstream>

namespace dlvhex {
  namespace mcsdiagexpl {

   	InputConverterExplanations* InputConverterExplanations::ice = NULL;

	InputConverterExplanations*
	InputConverterExplanations::getInstance() {
		if (ice == NULL) {
		  ice = new InputConverterExplanations();
		  //e->init();
		}
		return ice;
	}

   void
   InputConverterExplanations::convertParseTreeToDLVProgram(node_t& node, std::ostream& o) {
	InputConverterHelper* ich = InputConverterHelper::getInstance();

     if (!(node.value.id() == MCSdescriptionGrammar::Root)) {
       throw PluginError("MCS Equilibrium Plugin: Inputfile syntax error!");
     }
     bridgerules.clear();
     context.clear();

     for (node_t::tree_iterator it = node.children.begin(); 
       it != node.children.end(); ++it) {
       node_t& at = *it;
       #ifdef DEBUG
	std::cout << "Val ID: " << MCSdescriptionGrammar::RuleID << std::endl;
       #endif
       if (at.value.id() == MCSdescriptionGrammar::BridgeRule) {
	 #ifdef DEBUG
           printSpiritPT(std::cout, at, "BridgeRule");
	 #endif
         //create new Bridgerule elem and fill the vector with elements
	 BridgeRule bridgeRule = BridgeRule();
         ich->convertBridgeRule(at,bridgeRule);
         bridgerules.push_back(bridgeRule);
       } //end if-rule Bridgerule
       ////////////////////////////////////////////
       // If the Bridgerule is only a fact,      //
       // there is only a RuleHeadElement        //
       ////////////////////////////////////////////
       if (at.value.id() == MCSdescriptionGrammar::RuleHeadElem) {
	 #ifdef DEBUG
           printSpiritPT(std::cout, at, "BridgeRuleFact");
	 #endif
         //create new Bridgerule elem and fill the vector with elements
	 BridgeRule bridgeRule = BridgeRule(true);
         ich->convertBridgeRuleFact(at,bridgeRule);
	 //bridgeRule.writeProgram(std::cout);
         bridgerules.push_back(bridgeRule);
       } //end if-rule Bridgerule
       if (at.value.id() == MCSdescriptionGrammar::Context) {
         ParseContext c = ParseContext();
         ich->convertContext(at,c);
         context.push_back(c);
	 #ifdef DEBUG
	   printSpiritPT(std::cout, at, "Context");
         #endif
       } //end if-rule Context		
     } // end for-loop over all children of root

     ////////////////////////////////////////////////
     // write the Parsed Program in the out stream //
     // first write out the Rules an additional    //
     // output of the rules, then the              /#include "InputConverterDiagnosis.h"/
     // external Atom output for the context       //
     ////////////////////////////////////////////////
     for (std::vector<BridgeRule>::iterator it = bridgerules.begin(); it != bridgerules.end(); ++it) {
	BridgeRule elem = *it;
	writeProgram(o,elem);
     }//end for-loop print bridgerules
     int maxctx = 0;
     for (std::vector<ParseContext>::iterator it = context.begin(); it != context.end(); ++it) {
	ParseContext elem = *it;


	//8.) spoil if the guessed belief state is no equilibrium
	o << "spoil :- not &saturation_meta_context[\"" << elem.ExtAtom()  <<"\",spoil,"
		 << elem.ContextNum() << ",pres_" << elem.ContextNum() << ",in_" << elem.ContextNum()
		 << ",out_" << elem.ContextNum() << ",\"" << elem.Param() << "\"]." << std::endl; 

        if( elem.ContextNum() > maxctx )
          maxctx = elem.ContextNum();
     }//end for-loop print context



	//guess a subset of the candidate explanation
	// for which holds that E1 C_ r1 C_ brM and r2 C_ brM \ E2
	o << "foo3(r1). foo3(r2). foo3(r3)." << std::endl;
	o << "r1(R) :- e1(R), foo3(R)." << std::endl;
	o << "r1(R) v nr1(R) :- ne1(R), foo3(R)." << std::endl;
	o << "r2(R) v nr2(R) :- ne2(R), foo3(R)." << std::endl;
	
	// ensure saturation
	o << ":- not spoil." << std::endl;

	// data to make the medExample easier
	//o << "e1(r1)." << std::endl;
	//o << "e1(r2)." << std::endl;
	////o << "e1(r3)." << std::endl;
	//o << "e1(r4)." << std::endl;
	//o << "e2(r5).";


   } // end convertParseTreeToDLVProgramEx

void 
   InputConverterExplanations::writeProgram(std::ostream& o, BridgeRule br) {
     // write bridgerule in asp form
     std::list<int> ilist;


     std::stringstream iny;
     iny << "in_" << br.head.ContextID() << "(" << br.head.Fact() << ") :- r1(" << br.ruleid << ")";
     for (std::vector<BridgeRuleEntry>::iterator it = br.body.begin(); it != br.body.end(); ++it) {
       const BridgeRuleEntry& elem = *it;
       iny << ", pres_" << elem.ContextID() << "(" << elem.Fact() << ")";	

	// 3.) guess a belief state, every a e Outi
	o << "pres_" << elem.ContextID() << "(" << elem.Fact() << ") v abs_" << elem.ContextID() << "(" << elem.Fact() << ")." << std::endl;
	// 7.) i.e. OUTi, so Vo e OUTi add out_i(o)	
	o << "out_" << elem.ContextID() << "(" << elem.Fact() << ")." << std::endl;
	// 10.) saturate on spoil	
	o << "pres_" << elem.ContextID() << "(" << elem.Fact() << ") :- spoil." << std::endl;
	o << "abs_" << elem.ContextID() << "(" << elem.Fact() << ") :- spoil." << std::endl;
	//9.) spoil if our guesses are wrong by themselves.
	o << "spoil :- pres_" << elem.ContextID() << "(" << elem.Fact() << "), " << "abs_" << elem.ContextID() << "(" << elem.Fact() << ")." 
		<< std::endl;

     }
	iny << ".";

	// derive applicable rule heads
	o << iny.str() << std::endl;
	// derive heads of unconditional rules.
	o << "in_" << br.head.ContextID() << "(" << br.head.Fact() << ") :- r2(" << br.ruleid << ")." << std::endl;
	// 10.) saturate on spoil
	o << "in_" << br.head.ContextID() << "(" << br.head.Fact() << ") :- spoil." << std::endl;
	//9.) spoil if our guesses are wrong by themselves.
	o << "spoil :- r1(" << br.ruleid << "), " << "nr1(" << br.ruleid << ")." << std::endl;
	o << "spoil :- r2(" << br.ruleid << "), " << "nr2(" << br.ruleid << ")." << std::endl;
	
	//guess an explanation candidate.
	o << "e1(" << br.ruleid << ") v ne1(" << br.ruleid << ")." << std::endl;
	o << "e2(" << br.ruleid << ") v ne2(" << br.ruleid << ")." << std::endl;
	o << ":- e1(" << br.ruleid << "), ne1(" << br.ruleid << ")." << std::endl;
	o << ":- e2(" << br.ruleid << "), ne2(" << br.ruleid << ")." << std::endl;;

	//guess a subset of the candidate explanation
	// for which holds that E1 C_ r1 C_ brM and r2 C_ brM \ E2
	//o << "r1(" << br.ruleid << ") :- e1(" << br.ruleid << ")." << std::endl;
	//o << "r1(" << br.ruleid << ") v nr1(" << br.ruleid << ") :- ne1(" << br.ruleid << ")." << std::endl;
	//o << "r2(" << br.ruleid << ") v nr2(" << br.ruleid << ") :- ne2(" << br.ruleid << ")." << std::endl;

	// 10.) saturate on spoil	
	o << "r1(" << br.ruleid << ") :- spoil." << std::endl;
	o << "r2(" << br.ruleid << ") :- spoil." << std::endl;
	o << "nr1(" << br.ruleid << ") :- spoil." << std::endl;
	o << "nr2(" << br.ruleid << ") :- spoil." << std::endl;

     }




  } // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
