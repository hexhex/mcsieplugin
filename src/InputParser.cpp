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

} // anonymous namespace

namespace dlvhex {
namespace mcsdiagexpl {

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

 // store parse tree into MCS& out
#if 0
 // Convert the Parse Tree to a asp program
 std::stringstream ss;
 if (!Global::getInstance()->isCalculationOverExplanations()){
    InputConverterDiagnosis::getInstance()->convertParseTreeToDLVProgram(*info.trees.begin(), ss);
 }else{
    if (Global::getInstance()->isDiag()){
            //The calculation over explanations produces a superset of the actual diagnosis. some of the contained tuples may not be diagnosis.
            //If you want to print out the found superset remove this code, and enable the output code for diaagnosis in Outputrewriter.cpp
            std::cout << "A calculation over explanations cannot produce D, please choose an other value for parameter --ieexplain!" << std::endl;
            exit(0);
    }
    InputConverterExplanations::getInstance()->convertParseTreeToDLVProgram(*info.trees.begin(), ss);	
 }

 #ifdef DEBUG
   std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
   std::cout << "Converted DLV Program: " << std::endl;
   std::cout << ss.str();
   std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
 #endif
 o << ss.rdbuf();
#endif
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
