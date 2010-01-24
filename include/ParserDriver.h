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
 * @file   ParserDriver.h
 * @author Markus Boegl
 * @date   Sun Jan 24 13:50:13 2010
 * 
 * @brief  Defines Grammer of the Input File
 */
#ifndef _DLVHEX_MCSEQUILIBRIUM_PARSERDRIVER_H_
#define _DLVHEX_MCSEQUILIBRIUM_PARSERDRIVER_H_

#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/chset.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/tree/ast.hpp>

namespace dlvhex {
	namespace mcsequilibrium {

////////////////////////////////////////////////////////////////////////////
//
//  Grammer for MCS description
//
////////////////////////////////////////////////////////////////////////////
struct MCSdescriptionGrammar:
  public boost::spirit::grammar<MCSdescriptionGrammar>
{
  enum RuleTags {
    None = 0, Root, Expression, BridgeRule, RuleHeadElem, RuleBody, 
    RuleElem, NegRuleElem, RuleNum, Fact, Context, ContextNum, ExtAtom, Param, BridgeRuleFact };

  // S = ScannerT
  template<typename S>
  struct definition
  {
    // shortcut
    typedef boost::spirit::parser_context<> c;
    template<int Tag> struct tag: public boost::spirit::parser_tag<Tag> {};

    definition(MCSdescriptionGrammar const& self);
    boost::spirit::rule< S, c, tag<Root> > const& start() const { return root; }

    boost::spirit::rule<S, c, tag<Root> >        	root;		/* 01 */
    boost::spirit::rule<S, c, tag<Expression> >   	expression;	/* 02 */
    boost::spirit::rule<S, c, tag<BridgeRule> >   	bridgerule;	/* 03 */
    boost::spirit::rule<S, c, tag<RuleHeadElem> >      	ruleheadelem;	/* 04 */
    boost::spirit::rule<S, c, tag<RuleBody> >      	rulebody;	/* 05 */
    boost::spirit::rule<S, c, tag<RuleElem> >      	ruleelem;	/* 06 */
    boost::spirit::rule<S, c, tag<NegRuleElem> >      	negruleelem;	/* 07 */
    boost::spirit::rule<S, c, tag<RuleNum> >  		rulenum;	/* 08 */
    boost::spirit::rule<S, c, tag<Fact> >       	fact;		/* 09 */
    boost::spirit::rule<S, c, tag<Context> > 		context;	/* 10 */
    boost::spirit::rule<S, c, tag<ContextNum> >  	contextnum;	/* 11 */
    boost::spirit::rule<S, c, tag<ExtAtom> >      	extatom;	/* 12 */
    boost::spirit::rule<S, c, tag<Param> >         	param;		/* 13 */
    boost::spirit::rule<S, c, tag<BridgeRuleFact> >	bridgerulefact; /* 14 */
  };
};

template<typename ScannerT>
MCSdescriptionGrammar::definition<ScannerT>::definition(MCSdescriptionGrammar const&) {
  // shortcut for sp::discard_node_d()
  const boost::spirit::node_parser_gen<boost::spirit::discard_node_op> rm =
  boost::spirit::node_parser_gen<boost::spirit::discard_node_op>();

  boost::spirit::chset<> alnumdot("a-zA-Z0-9_./");
  boost::spirit::chset<> alnum_("a-zA-Z0-9_");

  rulenum = 
	boost::spirit::lexeme_d[boost::spirit::token_node_d[(+boost::spirit::digit_p)]];

  contextnum =
	boost::spirit::lexeme_d[boost::spirit::token_node_d[(+boost::spirit::digit_p)]];
  fact =
	boost::spirit::token_node_d[+alnum_];

  extatom =
	rm[boost::spirit::ch_p('"')] >> boost::spirit::token_node_d[+alnum_] >> rm[boost::spirit::ch_p('"')];

  param =
	rm[boost::spirit::ch_p('"')] >> boost::spirit::token_node_d[+alnumdot] >> rm[boost::spirit::ch_p('"')];

  ruleelem =
	rm[boost::spirit::ch_p('(')] >> rulenum >> 
	rm[boost::spirit::ch_p(':')] >> fact >> rm[boost::spirit::ch_p(')')];

  negruleelem =
	rm[boost::spirit::str_p("not")] >> rm[boost::spirit::ch_p('(')] >> 
	rulenum >> rm[boost::spirit::ch_p(':')] >> fact >> rm[boost::spirit::ch_p(')')];

  ruleheadelem =
	rm[boost::spirit::ch_p('(')] >> rulenum >> rm[boost::spirit::ch_p(':')] >> 
	fact >> rm[boost::spirit::ch_p(')')];

  rulebody =
	(ruleelem|negruleelem) >> *( rm[boost::spirit::ch_p(',')] >> (ruleelem|negruleelem) );

  bridgerule =
	ruleheadelem >> boost::spirit::no_node_d[boost::spirit::str_p(":-")] >> 
	rulebody >> boost::spirit::no_node_d[boost::spirit::ch_p('.')];

  bridgerulefact =
	ruleheadelem >> boost::spirit::no_node_d[boost::spirit::ch_p('.')]
      | ruleheadelem >> boost::spirit::no_node_d[boost::spirit::str_p(":-")] >> 
	boost::spirit::no_node_d[boost::spirit::ch_p('.')];

  context =
	boost::spirit::infix_node_d[contextnum >> ',' >> extatom >> ',' >> param];

  expression =
	bridgerule
      | bridgerulefact
      |	(boost::spirit::no_node_d[boost::spirit::str_p("#context(")] >> context >> 
	boost::spirit::no_node_d[boost::spirit::str_p(").")]);

  root =
	*rm[boost::spirit::comment_p("%")] >> expression >> 
	*(expression | rm[boost::spirit::comment_p("%")]) >> !boost::spirit::end_p;
};
} // END namespace mcsequilibrium
} // END namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUM_PARSERDRIVER_H_
