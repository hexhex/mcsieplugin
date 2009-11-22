#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "GenericContextAtom.h"

#include <unistd.h>
#include <climits>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>

namespace dlvhex {
  namespace mcsequilibrium {

GenericContextAtom::GenericContextAtom(std::string hex_atom) {
	addInputConstant();
	addInputPredicate();
	addInputPredicate();
	addInputPredicate();
	addInputConstant();
	setOutputArity(0);
}

bool
issmaller(string a, string b) {
  if (a.compare(b) <= 0)
    return true;
  return false;
}

void
GenericContextAtom::convertStringSet(AtomSet& as, set<string>& sset) {
  for (AtomSet::const_iterator ai = as.begin(); ai != as.end(); ++ai) {
    sset.insert(((*ai).getArgument(1)).getString());
  }
  //sort(sset.begin(),sset.end(),issmaller);
}

void
GenericContextAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
  std::set<std::string> oset,aset,bset,interset;

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

  convertStringSet(a,aset);
  convertStringSet(b,bset);
  convertStringSet(o,oset);

//  set_intersection(bset.begin(),bset.end(),oset.begin(),oset.end(),interset.begin());

  Tuple out;
//  if (interset.size() == aset.size())
//    if (equal(interset.begin(),interset.end(),aset.begin()))
      answer.addTuple(out);

  std::cout << "a_count: " << aset.size() << "\n";
  std::cout << "b_count: " << bset.size() << "\n";
  std::cout << "o_count: " << oset.size() << "\n";
}

  } // namespace script
} // namespace dlvhex
