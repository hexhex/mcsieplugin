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
 * @author Markus Boegl
 * @date   Sun Jan 24 13:34:29 2010
 * 
 * @brief  Converts the Input file
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "InputConverter.h"
#include "dlvhex/ASPSolver.h"
#include "dlvhex/SpiritDebugging.h"
#include "dlvhex/DLVProcess.h"
#include "dlvhex/PrintVisitor.h"
#include "BridgeRuleEntry.h"
#include "Global.h"

#include <boost/foreach.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <sstream>

namespace qi = boost::spirit::qi;

namespace dlvhex {
  namespace mcsdiagexpl {

   void
   InputConverter::convertBridgeRuleElem(node_t& at, std::string& ruleid, int& contextid, std::string& fact) {
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
   InputConverter::convertBridgeRuleFact(node_t& at, BridgeRule& brule) {
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
   }// End MCSequilibriumConverter::convertBridgeRule()

   void
   InputConverter::convertBridgeRule(node_t& at, BridgeRule& brule) {
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
   InputConverter::convertContext(node_t& at, ParseContext& context) {
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

   void
   InputConverter::convertParseTreeToDLVProgram(node_t& node, std::ostream& o) {
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
         convertBridgeRule(at,bridgeRule);
	 //bridgeRule.writeProgram(std::cout);
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
         convertBridgeRuleFact(at,bridgeRule);
	 //bridgeRule.writeProgram(std::cout);
         bridgerules.push_back(bridgeRule);
       } //end if-rule Bridgerule
       if (at.value.id() == MCSdescriptionGrammar::Context) {
         ParseContext c = ParseContext();
         convertContext(at,c);
         context.push_back(c);
	 #ifdef DEBUG
	   printSpiritPT(std::cout, at, "Context");
         #endif
       } //end if-rule Context		
     } // end for-loop over all children of root

     // we now have parsed the input
     // -> evaluate FVS via call to external DLV

     std::set<unsigned> fvsContexts;
     {
       std::ostringstream fvs;

       {
         // calculate maxint
         std::set<std::pair<int,std::string> > inputs;
         BOOST_FOREACH(const BridgeRule& rule, bridgerules)
         {
           inputs.insert(std::make_pair(rule.Head().ContextID(), rule.Head().Fact()));
         }
         fvs << "#maxint=" << inputs.size() << "." << std::endl;
       }

       BOOST_FOREACH(const ParseContext& ctx, context)
       {
         fvs << "ctx(c" << ctx.ContextNum() << ")." << std::endl;
       }
       BOOST_FOREACH(const BridgeRule& rule, bridgerules)
       {
         fvs << "input(c" << rule.Head().ContextID() << "," << rule.Head().Fact() << ")." << std::endl;
         BOOST_FOREACH(const BridgeRuleEntry& entry, rule.Body())
         {
           fvs << "dep(c" << rule.Head().ContextID() << ",c" << entry.ContextID() << ")." << std::endl;
         }
       }

       // count number of inputs of each context
       fvs << "inputs(Ctx,Number) :- ctx(Ctx), #int(Number), Number = #count { S : input(Ctx,S) }." << std::endl;
       // guess each context (in or out)
       fvs << "in(Ctx) v out(Ctx) :- ctx(Ctx)." << std::endl;
       // try to minimize the number of inputs in "out" contexts
       fvs << ":~ out(Ctx), inputs(Ctx, Number). [Number:1]" << std::endl;
       // evaluate reachability between contexts that are "in"
       fvs << "reach(Ctx1,Ctx2) :- dep(Ctx1,Ctx2), in(Ctx1), in(Ctx2)." << std::endl;
       fvs << "reach(Ctx1,Ctx3) :- reach(Ctx1,Ctx2), reach(Ctx2,Ctx3)." << std::endl;
       // forbid cycles -> find feedback vertex sets in "out"
       fvs << ":- reach(Ctx,Ctx)." << std::endl;

       std::vector<AtomSet> fvsResult;

       DLVProcess dlv;
       dlv.addOption("-nofacts");
       dlv.addOption("-silent");
       // take only first result
       dlv.addOption("-n=1");
       ASPStringSolver solver(dlv);
       solver.solve(fvs.str(), fvsResult);

       #if 0
       //std::cerr << "solved!" << fvsResult.size() << std::endl;
       DLVPrintVisitor visitor(std::cerr);
       BOOST_FOREACH(const AtomSet& as, fvsResult)
       {
         std::cerr << "answer set:" << std::endl;
         as.accept(visitor);
       }
       #endif

       // find set of "out" contexts in answer set
       assert(!fvsResult.empty());
       for(AtomSet::const_iterator at = fvsResult.front().begin();
           at != fvsResult.front().end(); ++at)
       {
         if( at->getPredicate() == "out" )
         {
           const std::string& arg = at->getArgument(1).getString();
           unsigned ctxNum;
           std::string::const_iterator it = arg.begin();
           qi::parse(it, arg.end(), 'c' > qi::uint_, ctxNum);
           //std::cerr << "found ctxNum " << ctxNum << std::endl;
           fvsContexts.insert(ctxNum);
         }
       }
     }

     // generate code for contexts
     BOOST_FOREACH(const ParseContext& ctx, context)
     {
       unsigned u = ctx.ContextNum();
       if( fvsContexts.count(u) == 0 )
       {
         // not a fvs context

         // output forward evaluation
         o << "aa" << u << "(H,B) :- o" << u << "(B), " <<
              "&" << ctx.ExtAtom() << "[b" << u << ",o" << u << ",\"" << ctx.Param() << "\"](H,B)." << std::endl;
       }
       else
       {
         // a fvs context

         // input guessing
         o << "bg" << u << "(S) v nbg" << u << "(S) :- in" << u << "(S)." << std::endl;

         // output forward evaluation
         o << "aa" << u << "(H,B) :- o" << u << "(B), " <<
              "&" << ctx.ExtAtom() << "[bg" << u << ",o" << u << ",\"" << ctx.Param() << "\"](H,B)." << std::endl;

         // guess vs calculated input verification
         o << ":- bg" << u << "(S), not b" << u << "(S)." << std::endl;
         o << ":- not bg" << u << "(S), b" << u << "(S)." << std::endl;
       }

       // guess handle
       o << "use" << u << "(H) v nuse" << u << "(H) :- aa" << u << "(H,B)." << std::endl;

       // choose no more than one handle by guessing
       o << ":- use" << u << "(H1), use" << u << "(H2), H1 != H2." << std::endl;

       // choose at least one handle by guessing
       o << "used" << u << " :- use" << u << "(H)." << std::endl;
       o << ":- not used" << u << "." << std::endl;

       // store chosen output in a<i>(belief) (just s.t. we don't need to change the
       // EquilibriumOutputVisitor)
       // store only if it is an output belief (for the workaround to return fact "0"
       // for answer sets which are empty)
       o << "a" << u << "(X) :- aa" << u << "(H,X), use" << u << "(H), o" << u << "(X)." << std::endl;
     }

     // generate code for bridge rules
     BOOST_FOREACH(const BridgeRule& rule, bridgerules)
     {
        const BridgeRuleEntry& head = rule.Head();
        // mark head as input
        o << "in" << head.ContextID() << "(" << head.Fact() << ")." << std::endl;

        // write rule
        o << "b" << head.ContextID() << "(" << head.Fact() << ")";
        if( rule.Body().empty() )
        {
          o << "." << std::endl;
        }
        else
        {
          o << " :- ";
          for(std::vector<BridgeRuleEntry>::const_iterator it = rule.Body().begin();
              it != rule.Body().end(); ++it)
          {
            unsigned ctx = it->ContextID();
            const std::string& fact = it->Fact();
            bool naf = it->Neg();
            if( it != rule.Body().begin() )
              o << ", ";
            o << "use" << ctx << "(H" << ctx << "), ";
            if( naf )
              o << "not ";
            o << "aa" << ctx << "(H" << ctx << "," << fact << ")";
          }
          o << "." << std::endl;

          // write each fact as context output
          for(std::vector<BridgeRuleEntry>::const_iterator it = rule.Body().begin();
              it != rule.Body().end(); ++it)
          {
            unsigned ctx = it->ContextID();
            const std::string& fact = it->Fact();
            o << "o" << ctx << "(" << fact << ")." << std::endl;
          }
        }
     }
   } // end convertParseTreeToDLVProgram

   void
   InputConverter::convert(std::istream& i, std::ostream& o) {
     MCSdescriptionGrammar mcsdgram;
     std::ostringstream buf;
     buf << i.rdbuf();
     std::string input = buf.str();

     iterator_t it_begin = input.c_str();
     iterator_t it_end = input.c_str() + input.size();

     boost::spirit::classic::tree_parse_info<iterator_t, factory_t> info = 
       boost::spirit::classic::ast_parse<factory_t>(it_begin, it_end, mcsdgram, boost::spirit::classic::space_p);

     if (!info.full) {
       throw PluginError("MCS Equilibrium Plugin: Inputfile syntax error!");
     }

     // if there's not 1 tree in the result of the parser, this is a bug
     assert(info.trees.size() == 1);

     // Convert the Parse Tree to a asp program
     std::stringstream ss;
     convertParseTreeToDLVProgram(*info.trees.begin(), ss);

     #ifdef DEBUG
       std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
       std::cout << "Converted DLV Program: " << std::endl;
       std::cout << ss.str();
       std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
     #endif
     o << ss.rdbuf();
   } // end of MCSequilibriumConverter::convert

  } // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
