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
 * @file   InputConverterOPEquilibria.cpp
 * @author Peter Schueller
 * 
 * @brief  Realizes rewriting to obtain output projected equilibria.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "InputConverterOPEquilibria.h"
//#include "dlvhex/SpiritDebugging.h"
//#include "BridgeRuleEntry.h"
//#include "Global.h"
//#include "InputConverterDiagnosis.h"


#include <iostream>
#include <sstream>

namespace dlvhex {
namespace mcsdiagexpl {

void InputConverterOPEquilibria::convert(std::istream& i, std::ostream& o)
{
  throw std::runtime_error("todo InputConverterOPEquilibria?::convert");
}

#if 0
 context print

     const int cn = context.ContextNum();

     if( Global::getInstance()->isKR2010rewriting() )
     {
       // guess outputs
       out << "ma" << cn << "(X) v nma" << cn << "(X) :- o" << cn << "(X)." << std::endl;

       // check context with constraint
       out << ":- not &" << context.ExtAtom()
           << "[" << cn << ",ma" << cn << ",mb" << cn << ",o" << cn << ","
           << "\"" << context.Param() << "\"]()." << std::endl; 

       // mark context as existing
       out << "ctx(" << cn << ")." << std::endl;
     }
     else
     {
       // guess input and output beliefs (after previous context has been finished)

       // inputs
       out << "mb" << cn << "(X) v nmb" << cn << "(X) :- i" << cn << "(X)";
       out << ", ok(" << (cn-1) << ")";
       out << "." << std::endl;

       // outputs
       out << "ma" << cn << "(X) v nma" << cn << "(X) :- o" << cn << "(X)";
       out << ", ok(" << (cn-1) << ")";
       out << "." << std::endl;

       // context check
       out << "ok(" << cn << ") :- &" << context.ExtAtom() 
         << "[" << context.ContextNum()
         << ",ma" << context.ContextNum()
         << ",mb" << context.ContextNum() 
         << ",o" << context.ContextNum()
         << ",\"" << context.Param() << "\"]()";
       out << ", ok(" << (cn-1) << ")";
       out << "." << std::endl;

       // require that context check is successful
       out << ":- not ok(" << cn << ")." << std::endl;

       // verify guessed output with output calculated via bridge rules (if all contexts are ok)
       out << ":- mc" << cn << "(X), not mb" << cn << "(X), ok(all)." << std::endl;
       out << ":- not mc" << cn << "(X), mb" << cn << "(X), ok(all)." << std::endl;

       // mark context as existing
       out << "ctx(" << cn << ")." << std::endl;
     }
     return out;
   }

#endif

#if 0
   void 
   BridgeRule::writeProgram(std::ostream& o) {
     // write bridgerule in asp form
     std::list<int> ilist;

     // mark outputs: OUT_i via "o<i>(belief)"
     for (std::vector<BridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
       const BridgeRuleEntry& elem = *it;
       o << "o" << elem << "." << std::endl;
     }

     if ((Global::getInstance())->isKR2010rewriting())
     {
       if ((Global::getInstance())->isSet()) {
       // Only print equilibria
         // output diagnosis disjunction
         o << "normal(" << ruleid << ") v md1(" << ruleid << ") v md2(" << ruleid << ")." << std::endl;
         // output d2 rule
         o << "mb" << head << " :- md2(" << ruleid << ")." << std::endl;
         // output d1 rule
         o << "mb" << head << " :- not md1(" << ruleid << ")";
         if (fact)
           o << "." << std::endl;
         else
           o << ", ";
       } else {
         o << "mb" << head;
         if (fact)
           o << "." << std::endl;
         else
           o << " :- ";
       }
     }
     else
     {
       // mark inputs: IN_i via "i<i>(belief)"
       o << "i" << head << "." << std::endl;

       // BR evaluation (and diagnosis guessing) (after all contexts ok, indicated by ok(all))
       if ((Global::getInstance())->isSet())
       {
         // diagnosis guessing
         o << "normal(" << ruleid << ") v md1(" << ruleid << ") v md2(" << ruleid << ") :- ok(all)." << std::endl;
         // d2 rule
         o << "mc" << head << " :- md2(" << ruleid << "), ok(all)." << std::endl;
         // d1 rule
         o << "mc" << head << " :- not md1(" << ruleid << "), ok(all)";
         if (fact)
           o << "." << std::endl;
         else
           o << ", ";
       }
       else
       {
         // else only print equilibria
         o << "mc" << head;
         if (fact)
           o << "." << std::endl;
         else
           o << " :- ";
       }
     }

     // output bridge rule body
     for (std::vector<BridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
       const BridgeRuleEntry& elem = *it;
       if (elem.Neg())
         o << "n";
       o << "ma" << elem;
       if (it+1 != body.end())
         o << ", ";
       else
         o << "." << std::endl;
     }
   }

#endif
#if 0
   	InputConverterDiagnosis* InputConverterDiagnosis::icd = NULL;

	InputConverterDiagnosis*
	InputConverterDiagnosis::getInstance() {
		if (icd == NULL) {
		  icd = new InputConverterDiagnosis();
		  //e->init();
		}
		return icd;
	}

   void
   InputConverterDiagnosis::convertParseTreeToDLVProgram(node_t& node, std::ostream& o) {
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
         ich->convertBridgeRuleFact(at,bridgeRule);;
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
     // output of the rules, then the              //
     // external Atom output for the context       //
     ////////////////////////////////////////////////
     for (std::vector<BridgeRule>::iterator it = bridgerules.begin(); it != bridgerules.end(); ++it) {
	BridgeRule elem = *it;
	writeProgram(o, elem);
     }//end for-loop print bridgerules
     int maxctx = 0;
     for (std::vector<ParseContext>::iterator it = context.begin(); it != context.end(); ++it) {
	ParseContext elem = *it;
	o << elem;
        if( elem.ContextNum() > maxctx )
          maxctx = elem.ContextNum();
     }//end for-loop print context

     if( !Global::getInstance()->isKR2010rewriting() )
     {
       // zeroe'th context is ok by default
       o << "ok(0)." << std::endl;
       // all contexts are ok if the last one is ok
       o << "ok(all) :- ok(" << maxctx << ")." << std::endl;
     }
   } // end convertParseTreeToDLVProgram


void 
   InputConverterDiagnosis::writeProgram(std::ostream& o, BridgeRule br) {
     // write bridgerule in asp form
     std::list<int> ilist;

     // mark outputs: OUT_i via "o<i>(belief)"
     for (std::vector<BridgeRuleEntry>::iterator it = br.body.begin(); it != br.body.end(); ++it) {
       const BridgeRuleEntry& elem = *it;
       o << "o" << elem << "." << std::endl;
     }

     if ((Global::getInstance())->isKR2010rewriting())
     {
       if ((Global::getInstance())->isSet()) {
       // Only print equilibria
         // output diagnosis disjunction
         o << "normal(" << br.ruleid << ") v d1(" << br.ruleid << ") v d2(" << br.ruleid << ")." << std::endl;
         // output d2 rule
         o << "b" << br.head << " :- d2(" << br.ruleid << ")." << std::endl;
         // output d1 rule
         o << "b" << br.head << " :- not d1(" << br.ruleid << ")";
         if (br.fact)
           o << "." << std::endl;
         else
           o << ", ";
       } else {
         o << "b" << br.head;
         if (br.fact)
           o << "." << std::endl;
         else
           o << " :- ";
       }
     }
     else
     {
       // mark inputs: IN_i via "i<i>(belief)"
       o << "i" << br.head << "." << std::endl;

       // BR evaluation (and diagnosis guessing) (after all contexts ok, indicated by ok(all))
       if ((Global::getInstance())->isSet())
       {
         // diagnosis guessing
         o << "normal(" << br.ruleid << ") v d1(" << br.ruleid << ") v d2(" << br.ruleid << ") :- ok(all)." << std::endl;
         // d2 rule
         o << "c" << br.head << " :- d2(" << br.ruleid << "), ok(all)." << std::endl;
         // d1 rule
         o << "c" << br.head << " :- not d1(" << br.ruleid << "), ok(all)";
         if (br.fact)
           o << "." << std::endl;
         else
           o << ", ";
       }
       else
       {
         // else only print equilibria
         o << "c" << br.head;
         if (br.fact)
           o << "." << std::endl;
         else
           o << " :- ";
       }
     }

     // output bridge rule body
     for (std::vector<BridgeRuleEntry>::iterator it = br.body.begin(); it != br.body.end(); ++it) {
       const BridgeRuleEntry& elem = *it;
       if (elem.Neg())
         o << "n";
       o << "a" << elem;
       if (it+1 != br.body.end())
         o << ", ";
       else
         o << "." << std::endl;
     }
   }


#endif

  } // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
