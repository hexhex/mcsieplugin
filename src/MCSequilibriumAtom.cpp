#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSequilibriumAtom.h"

#include <unistd.h>
#include <climits>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <string>

namespace dlvhex {
  namespace mcsequilibrium {

MCSequilibriumAtom::MCSequilibriumAtom() {
	addInputPredicate();
	addInputPredicate();
	addInputPredicate();
	addInputConstant();
	setOutputArity(0);
}


void
MCSequilibriumAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
	int ai = 0,bi=0,oi=0;
	std::string in = query.getInputTuple()[3].getUnquotedString();
	std::cout << "Constant: " << in << "\n";
	AtomSet input = query.getInterpretation();

	AtomSet a;
	input.matchPredicate("a",a);
	AtomSet b;
	input.matchPredicate("b",b);
	AtomSet o;
	input.matchPredicate("o",o);

	AtomSet::const_iterator a_cur = a.begin();
	AtomSet::const_iterator a_last = a.end();
	AtomSet::const_iterator b_cur = b.begin();
	AtomSet::const_iterator b_last = b.end();
	AtomSet::const_iterator o_cur = o.begin();
	AtomSet::const_iterator o_last = o.end();

	while (a_cur != a_last) {
		ai++;
		a_cur++;
	}
	while (b_cur != b_last) {
		bi++;
		b_cur++;
	}
	while (o_cur != o_last) {
		oi++;
		o_cur++;
	}


    
    Tuple out;
    std::string t("e");
    //out.push_back(Term(in2, false));
	if (in == "acc") {
		answer.addTuple(out);
	}
	std::cout << "a_count: " << ai << "\n";
	std::cout << "b_count: " << bi << "\n";
	std::cout << "o_count: " << oi << "\n";
}

  } // namespace script
} // namespace dlvhex
