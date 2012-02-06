/* dlvhex-mcs-equilibrium-plugin -- Inconsistency analysis and equilibrium
 * semantics for heterogeneous nonmonotonic Multi-Context Systems in dlvhex.
 * Copyright (C) 2009,2010 Markus Boegl
 * Copyright (C) 2011 Gerald Weidinger
 * Copyright (C) 2012 Peter Schueller
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
 * @file   	InputParser.cpp
 * @author 	Markus Boegl
 * @author 	Gerad Weidinger
 * @author 	Peter Schueller
 * @date   	Sun Jan 08 13:34:29 2011
 * 
 * @brief       parses input into internal representation and creates rewritten program
 *
 * internal representation of MCS is in ProgramCtxData
 * configuration of rewriting is in ProgramCtxData
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "InputParser.h"

#include <dlvhex2/Logger.h>
#include <dlvhex2/Error.h>

//#define DEBUG

//#include "dlvhex/SpiritDebugging.h"
//#include "BridgeRuleEntry.h"
//#include "InputConverterDiagnosis.h"
//#include "InputConverterExplanations.h"

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_chset.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_parse_tree.hpp>
#include <boost/spirit/include/classic_ast.hpp>

#include <iostream>
#include <sstream>

namespace dlvhex {
namespace mcsdiagexpl {

namespace
{

typedef boost::spirit::classic::node_val_data_factory<> factory_t;
typedef const char* iterator_t;
typedef boost::spirit::classic::tree_match<iterator_t, factory_t>::node_t node_t;

////////////////////////////////////////////////////////////////////////////
//
//  Grammer for MCS description
//
////////////////////////////////////////////////////////////////////////////
struct MCSdescriptionGrammar:
  public boost::spirit::classic::grammar<MCSdescriptionGrammar>
{
  enum RuleTags {
    None = 0, Root, Expression, BridgeRule, RuleHeadElem, RuleBody, 
    RuleElem, NegRuleElem, RuleNum, Fact, Context, ContextNum, ExtAtom, Param, BridgeRuleFact, RuleID };

  // S = ScannerT
  template<typename S>
  struct definition
  {
    // shortcut
    typedef boost::spirit::classic::parser_context<> c;
    template<int Tag> struct tag: public boost::spirit::classic::parser_tag<Tag> {};

    definition(MCSdescriptionGrammar const& self);
    boost::spirit::classic::rule< S, c, tag<Root> > const& start() const { return root; }

    boost::spirit::classic::rule<S, c, tag<Root> >        	root;		/* 01 */
    boost::spirit::classic::rule<S, c, tag<Expression> >   	expression;	/* 02 */
    boost::spirit::classic::rule<S, c, tag<BridgeRule> >   	bridgerule;	/* 03 */
    boost::spirit::classic::rule<S, c, tag<RuleHeadElem> >      ruleheadelem;	/* 04 */
    boost::spirit::classic::rule<S, c, tag<RuleBody> >      	rulebody;	/* 05 */
    boost::spirit::classic::rule<S, c, tag<RuleElem> >      	ruleelem;	/* 06 */
    boost::spirit::classic::rule<S, c, tag<NegRuleElem> >      	negruleelem;	/* 07 */
    boost::spirit::classic::rule<S, c, tag<RuleNum> >  		rulenum;	/* 08 */
    boost::spirit::classic::rule<S, c, tag<Fact> >       	fact;		/* 09 */
    boost::spirit::classic::rule<S, c, tag<Context> > 		context;	/* 10 */
    boost::spirit::classic::rule<S, c, tag<ContextNum> >  	contextnum;	/* 11 */
    boost::spirit::classic::rule<S, c, tag<ExtAtom> >      	extatom;	/* 12 */
    boost::spirit::classic::rule<S, c, tag<Param> >         	param;		/* 13 */
    boost::spirit::classic::rule<S, c, tag<BridgeRuleFact> >	bridgerulefact; /* 14 */
    boost::spirit::classic::rule<S, c, tag<RuleID> >  		ruleid;		/* 15 */
  };
};

template<typename ScannerT>
MCSdescriptionGrammar::definition<ScannerT>::definition(MCSdescriptionGrammar const&) {
  // shortcut for sp::discard_node_d()
  const boost::spirit::classic::node_parser_gen<boost::spirit::classic::discard_node_op> rm =
  boost::spirit::classic::node_parser_gen<boost::spirit::classic::discard_node_op>();

  boost::spirit::classic::chset<> alnumdot("a-zA-Z0-9_./");
  boost::spirit::classic::chset<> alnum_("a-zA-Z0-9_");

  ruleid =
	boost::spirit::classic::lexeme_d[boost::spirit::classic::token_node_d[+alnum_]];

  rulenum = 
	boost::spirit::classic::lexeme_d[boost::spirit::classic::token_node_d[(+boost::spirit::classic::digit_p)]];

  contextnum =
	boost::spirit::classic::lexeme_d[boost::spirit::classic::token_node_d[(+boost::spirit::classic::digit_p)]];
  fact =
	boost::spirit::classic::token_node_d[+alnum_];

  extatom =
	rm[boost::spirit::classic::ch_p('"')] >> boost::spirit::classic::token_node_d[+alnum_] >> rm[boost::spirit::classic::ch_p('"')];

  param =
	rm[boost::spirit::classic::ch_p('"')] >> boost::spirit::classic::token_node_d[*(~boost::spirit::classic::ch_p('"'))] >> rm[boost::spirit::classic::ch_p('"')];

  ruleelem =
	rm[boost::spirit::classic::ch_p('(')] >> rulenum >> 
	rm[boost::spirit::classic::ch_p(':')] >> fact >> rm[boost::spirit::classic::ch_p(')')];

  negruleelem =
	rm[boost::spirit::classic::str_p("not")] >> rm[boost::spirit::classic::ch_p('(')] >> 
	rulenum >> rm[boost::spirit::classic::ch_p(':')] >> fact >> rm[boost::spirit::classic::ch_p(')')];

  ruleheadelem =
	ruleid >> rm[boost::spirit::classic::ch_p(':')] >>
	rm[boost::spirit::classic::ch_p('(')] >> rulenum >> rm[boost::spirit::classic::ch_p(':')] >> 
	fact >> rm[boost::spirit::classic::ch_p(')')];

  rulebody =
	(ruleelem|negruleelem) >> *( rm[boost::spirit::classic::ch_p(',')] >> (ruleelem|negruleelem) );

  bridgerule =
	ruleheadelem >> boost::spirit::classic::no_node_d[boost::spirit::classic::str_p(":-")] >> 
	rulebody >> boost::spirit::classic::no_node_d[boost::spirit::classic::ch_p('.')];

  bridgerulefact =
	ruleheadelem >> boost::spirit::classic::no_node_d[boost::spirit::classic::ch_p('.')]
      | ruleheadelem >> boost::spirit::classic::no_node_d[boost::spirit::classic::str_p(":-")] >> 
	boost::spirit::classic::no_node_d[boost::spirit::classic::ch_p('.')];

  context =
	boost::spirit::classic::infix_node_d[contextnum >> ',' >> extatom >> ',' >> param];

  expression =
	bridgerule
      | bridgerulefact
      |	(boost::spirit::classic::no_node_d[boost::spirit::classic::str_p("#context(")] >> context >> 
	boost::spirit::classic::no_node_d[boost::spirit::classic::str_p(").")]);

  root =
	*rm[boost::spirit::classic::comment_p("%")] >> expression >> 
	*(expression | rm[boost::spirit::classic::comment_p("%")]) >> !boost::spirit::classic::end_p;

  #ifdef BOOST_SPIRIT_DEBUG
  BOOST_SPIRIT_DEBUG_NODE(root);
  BOOST_SPIRIT_DEBUG_NODE(expression);
  BOOST_SPIRIT_DEBUG_NODE(bridgerule);
  BOOST_SPIRIT_DEBUG_NODE(ruleheadelem);
  BOOST_SPIRIT_DEBUG_NODE(rulebody);
  BOOST_SPIRIT_DEBUG_NODE(ruleelem);
  BOOST_SPIRIT_DEBUG_NODE(negruleelem);
  BOOST_SPIRIT_DEBUG_NODE(rulenum);
  BOOST_SPIRIT_DEBUG_NODE(fact);
  BOOST_SPIRIT_DEBUG_NODE(context);
  BOOST_SPIRIT_DEBUG_NODE(contextnum);
  BOOST_SPIRIT_DEBUG_NODE(extatom);
  BOOST_SPIRIT_DEBUG_NODE(param);
  BOOST_SPIRIT_DEBUG_NODE(bridgerulefact);
  BOOST_SPIRIT_DEBUG_NODE(ruleid);
  #endif
};

void
convertBridgeRuleElem(node_t& at, std::string& ruleid, int& contextid, std::string& fact) {
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
convertBridgeRuleFact(node_t& at, BridgeRule& brule) {
   int cid;
   std::string f,rid;
   if (at.value.id() == MCSdescriptionGrammar::RuleHeadElem) {
       DBGLOG(DBG,"HeadElem");
       assert(at.children.size() == 3);
       convertBridgeRuleElem(at,rid,cid,f);
       brule.setHeadRule(rid,cid,f);
   }//end if-rule bridgeruleheadelem
}// End MCSequilibriumConverter::convertBridgeExplanationUnit::getInstance()->Rule()

void
convertBridgeRule(node_t& at, BridgeRule& brule) {
   int cid;
   std::string f, rid;
   for (node_t::tree_iterator ait = at.children.begin(); ait != at.children.end(); ++ait) {
     node_t& bat = *ait;
     ////////////////////////////////////////////
     // get the Head of the BridgeRule         //
     ////////////////////////////////////////////
     if (bat.value.id() == MCSdescriptionGrammar::RuleHeadElem) {
       DBGLOG(DBG,"HeadElem");
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
	   assert(bbeat.children.size()==2);
	   convertBridgeRuleElem(bbeat,rid,cid,f);
	   brule.addBodyRule(cid,f,false);
	 }//end if-rule for RuleElem in BridgeRuleBody
	 if (bbeat.value.id() == MCSdescriptionGrammar::NegRuleElem) {
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
       DBGLOG(DBG,"RuleElem");
       assert(bat.children.size()==2);
       convertBridgeRuleElem(bat,rid,cid,f);
       brule.addBodyRule(cid,f,false);
     }//end if-rule for RuleElem in BridgeRuleBody
     if (bat.value.id() == MCSdescriptionGrammar::NegRuleElem) {
       DBGLOG(DBG,"NegRuleElem");
       assert(bat.children.size()==2);
       convertBridgeRuleElem(bat,rid,cid,f);
       brule.addBodyRule(cid,f,true);
     }//end if-rule for negated RuleElem in BridgeRuleBody
   } //end for-loop over bridgerules
}// End MCSequilibriumConverter::convertBridgeRule()

void
convertContext(node_t& at, Context& context) {
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
   context = Context(id,extatom,param);
}// END MCSequilibriumConverter::convertContext

void convertParseTree(node_t& node, MCS& out)
{
  assert(node.value.id() == MCSdescriptionGrammar::Root);

  for(node_t::tree_iterator it = node.children.begin(); 
     it != node.children.end(); ++it) {
   node_t& at = *it;
   if (at.value.id() == MCSdescriptionGrammar::BridgeRule) {
     DBGLOG(DBG,"BridgeRule");
     //create new Bridgerule elem and fill the vector with elements
     out.rules.push_back(BridgeRule());
     convertBridgeRule(at,out.rules.back());
   } //end if-rule Bridgerule
   ////////////////////////////////////////////
   // If the Bridgerule is only a fact,      //
   // there is only a RuleHeadElement        //
   ////////////////////////////////////////////
   if (at.value.id() == MCSdescriptionGrammar::RuleHeadElem) {
     DBGLOG(DBG,"BridgeRuleFact");
     //create new Bridgerule elem and fill the vector with elements
     out.rules.push_back(BridgeRule(true));
     convertBridgeRuleFact(at,out.rules.back());
   } //end if-rule Bridgerule
   if (at.value.id() == MCSdescriptionGrammar::Context) {
     DBGLOG(DBG,"Context");
     out.contexts.push_back(Context());
     convertContext(at,out.contexts.back());
   } //end if-rule Context		
  } // end for-loop over all children of root
} // void convertParseTree(node_t& node, MCS& out)

} // anonymous namespace

void InputParser::parse(std::istream& i, MCS& out)
{
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

 convertParseTree(info.trees.front(), out);

 // store parse tree into MCS& out
 LOG(DBG,"parsed MCS representation:\n" << out);
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
