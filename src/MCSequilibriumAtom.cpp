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
	addInputConstant();
	addInputPredicate();
	addInputPredicate();
	addInputPredicate();
	addInputConstant();
	setOutputArity(0);
}


void
MCSequilibriumAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
	std::set<std::string> oset,aset,bset;

	int cid = query.getInputTuple()[0].getInt();
	std::cout << "Context ID: " << cid << "\n";

	std::stringstream ass, bss, oss;
	ass << "a" << cid;
	std::string ai_match(ass.str());
	bss << "b" << cid;
	std::string bi_match(bss.str());
	oss << "o" << cid;
	std::string oi_match(oss.str());

	std::string param = query.getInputTuple()[4].getUnquotedString();
	std::cout << "Param: " << param << "\n";

	AtomSet input = query.getInterpretation();

	AtomSet a;
	input.matchPredicate(ai_match,a);
	AtomSet b;
	input.matchPredicate(bi_match,b);
	AtomSet o;
	input.matchPredicate(oi_match,o);

	for (AtomSet::const_iterator oi = o.begin(); oi != o.end(); ++oi) {
	  std::cout << (*oi).getArguments() << std::endl;
	  //oset.push_back((*oi).getArguments());
	}

    
    Tuple out;
    std::string t("e");
    //out.push_back(Term(in2, false));
	if (param == "acc") {
		answer.addTuple(out);
	}
	std::cout << "a_count: " << a.size() << "\n";
	std::cout << "b_count: " << b.size() << "\n";
	std::cout << "o_count: " << o.size() << "\n";
}

  } // namespace script
} // namespace dlvhex
