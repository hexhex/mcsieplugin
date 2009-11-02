#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSequilibriumAtom.h"

#include <unistd.h>
#include <climits>
#include <cstring>
#include <sstream>
#include <cstdlib>

namespace dlvhex {
  namespace mcsequilibrium {

MCSequilibriumAtom::MCSequilibriumAtom() {
    addInputConstant();
    setOutputArity(0);
}


void
MCSequilibriumAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {

    std::string in = query.getInputTuple()[0].getUnquotedString();
    Tuple out;
    //out.push_back(Term(in,1));
    answer.addTuple(out);
}

  } // namespace script
} // namespace dlvhex
