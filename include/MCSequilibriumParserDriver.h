#ifndef _DLVHEX_MCSEQUILIBRIUMPARSERDRIVER_H
#define _DLVHEX_MCSEQUILIBRIUMPARSERDRIVER_H

#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/chset.hpp>

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
    None = 0, Root, Expression, BridgeRule, Context, Num, Param, Text, RuleElem };

  // S = ScannerT
  template<typename S>
  struct definition
  {
    // shortcut
    typedef boost::spirit::parser_context<> c;
    template<int Tag> struct tag: public boost::spirit::parser_tag<Tag> {};

    definition(MCSdescriptionGrammar const& self);
    boost::spirit::rule< S, c, tag<Root> > const& start() const { return root; }

    boost::spirit::rule<S, c, tag<Root> >        	root;
    boost::spirit::rule<S, c, tag<Expression> >   	expression;
    boost::spirit::rule<S, c, tag<BridgeRule> >   	bridgerule;
    boost::spirit::rule<S, c, tag<Context> > 		context;
    boost::spirit::rule<S, c, tag<Num> >  		num;
    boost::spirit::rule<S, c, tag<Param> >         	param;
    boost::spirit::rule<S, c, tag<Text> >       	text;
    boost::spirit::rule<S, c, tag<RuleElem> >      	ruleelem;
  };
};

template<typename ScannerT>
MCSdescriptionGrammar::definition<ScannerT>::definition(MCSdescriptionGrammar const&)
{
		chset<> alnum_("a-zA-Z0-9_");
		num
    			=	lexeme_d[(+digit_p)];

		
		text
			=	+alnum_;

		param
			=	'"' >> text >> '"';

		ruleelem
			=	'(' >> num >> ':' >> text >> ')';

		bridgerule
			=	ruleelem >> ":-" >> ruleelem >> 
			*(	',' >> ruleelem ) >>
			*(	',' >> str_p("not") >> ruleelem >> *(',' >> str_p("not") >> ruleelem)) >> '.';

		context
			=	num >> ',' >> text >> ',' >> param;


		expression
			=	bridgerule
			|	("#context(" >> context >> ").");

		root
			=	*expression >> !end_p;
};
} // END namespace mcsequilibriumparserdriver
} // END namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUMPARSERDRIVER_H



// Local Variables:
// mode: C++
// End:
