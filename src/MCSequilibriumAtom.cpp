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

namespace dlvhex {
  namespace mcsequilibrium {

MCSequilibriumAtom::MCSequilibriumAtom() {
    addInputConstant();
	addInputConstant();
    setOutputArity(1);
}


void
MCSequilibriumAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {

    std::string in = query.getInputTuple()[0].getUnquotedString();
	std::string in2 = query.getInputTuple()[1].getUnquotedString();
    Tuple out;
    std::string t("e");
    out.push_back(Term(in2, false));
	if (in == "acc") {
		answer.addTuple(out);
	}
}

  } // namespace script
} // namespace dlvhex
