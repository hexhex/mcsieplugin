#ifndef _DLVHEX_MCSEQUILIBRIUM_PARSERDRIVER_H
#define _DLVHEX_MCSEQUILIBRIUM_PARSERDRIVER_H

#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/chset.hpp>
#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/tree/ast.hpp>

namespace dlvhex {
	namespace mcsequilibrium {

////////////////////////////////////////////////////////////////////////////
//
//  Grammer for MCS description
//
////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace boost::spirit;
// "The Grammar"
struct MCSdescriptionGrammar:
  public grammar<MCSdescriptionGrammar>
{
  enum RuleTags {
    None = 0, Root, Expression, BridgeRule, RuleHeadElem, RuleBody, RuleElem, NegRuleElem, RuleNum, Fact, Context, ContextNum, ExtAtom, Param };

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
  };
};

template<typename ScannerT>
MCSdescriptionGrammar::definition<ScannerT>::definition(MCSdescriptionGrammar const&)
{
		// shortcut for sp::discard_node_d()
		const node_parser_gen<discard_node_op> rm =
		node_parser_gen<discard_node_op>();

		chset<> alnumdot("a-zA-Z0-9_.");
		chset<> alnum_("a-zA-Z0-9_");
		rulenum
    			=	lexeme_d[token_node_d[(+digit_p)]];

		contextnum
    			=	lexeme_d[token_node_d[(+digit_p)]];
		
		fact
			=	token_node_d[+alnum_];

		extatom
			=	token_node_d[+alnum_];

		param
			=	rm[ch_p('"')] >> token_node_d[+alnumdot] >> rm[ch_p('"')];

		ruleelem
			=	rm[ch_p('(')] >> rulenum >> rm[ch_p(':')] >> fact >> rm[ch_p(')')];

		negruleelem
			=	rm[str_p("not")] >> rm[ch_p('(')] >> rulenum >> rm[ch_p(':')] >> fact >> rm[ch_p(')')];

		ruleheadelem
			=	rm[ch_p('(')] >> rulenum >> rm[ch_p(':')] >> fact >> rm[ch_p(')')];

		rulebody
			=	ruleelem >> *(rm[ch_p(',')] >> ruleelem ) >> 
				*( rm[ch_p(',')] >> negruleelem);

		bridgerule// =	ruleheadelem >> rm[str_p(":-")] >> rulebody >> rm[ch_p('.')];
			=	ruleheadelem >> no_node_d[str_p(":-")] >> rulebody >> no_node_d[ch_p('.')];

		context// =	contextnum >> rm[ch_p(',')] >> extatom >> rm[ch_p(',')] >> param;
			=	infix_node_d[contextnum >> ',' >> extatom >> ',' >> param];

		expression
			=	bridgerule
			|	(no_node_d[str_p("#context(")] >> context >> no_node_d[str_p(").")]);

		root
			=	*expression >> !end_p;
};
} // END namespace mcsequilibriumparserdriver
} // END namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUM_PARSERDRIVER_H



// Local Variables:
// mode: C++
// End:
