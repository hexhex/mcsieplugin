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

GenericContextAtom::GenericContextAtom(std::string name) : hex_atom_name(name+"_context_acc") {
	addInputConstant();
	addInputPredicate();
	addInputPredicate();
	addInputPredicate();
	addInputConstant();
	setOutputArity(0);
}
/*
bool
issmaller(string a, string b) {
  if (a.compare(b) <= 0)
    return true;
  return false;
}
*/
void
GenericContextAtom::convertAtomSetToStringSet(AtomSet& as, set<string>& sset) {
  for (AtomSet::const_iterator ai = as.begin(); ai != as.end(); ++ai) {
    sset.insert(((*ai).getArgument(1)).getString());
  }
  //sort(sset.begin(),sset.begin()+sset.size());
}

void
GenericContextAtom::convertQueryToStringSets(const Query& query, set<string>& aset, set<string>& bset, set<string>& oset) throw (PluginError) {
  int cid = query.getInputTuple()[0].getInt();

  std::stringstream ass, bss, oss;
  ass << "a" << cid;
  std::string ai_match(ass.str());
  bss << "b" << cid;
  std::string bi_match(bss.str());
  oss << "o" << cid;
  std::string oi_match(oss.str());

  AtomSet input = query.getInterpretation();

  AtomSet a;
  input.matchPredicate(ai_match,a);
  AtomSet b;
  input.matchPredicate(bi_match,b);
  AtomSet o;
  input.matchPredicate(oi_match,o);

  convertAtomSetToStringSet(a,aset);
  convertAtomSetToStringSet(b,bset);
  convertAtomSetToStringSet(o,oset);

}

void printSet(string s) {
	cout << s << endl;
}

void
GenericContextAtom::stringset_intersection(const set<string>& aset, const set<string>& bset, set<string>& result) {
  set<string>::iterator ita,itb;
  ita = aset.begin();
  itb = bset.begin();
  while (ita != aset.end() && itb != bset.end()) {
    if (*ita < *itb) ++ita;
    else if (*itb < *ita) ++itb;
    else {
      result.insert(*ita);
      ita++;
      itb++;
    }
  }
}

void
GenericContextAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
  std::set<std::string> oset,aset,bset;
  set<string> interset, accset;

  std::string param = query.getInputTuple()[4].getUnquotedString();
  convertQueryToStringSets(query,aset,bset,oset);

  accset = acc(param,bset);
  stringset_intersection(accset,oset,interset);

/*  cout << "a set contains: \n";
  for_each (aset.begin(), aset.end(), printSet);
  cout << "---------------------------\n";
  cout << "b set contains: \n";
  for_each (bset.begin(), bset.end(), printSet);
  cout << "---------------------------\n";
  cout << "o set contains: \n";
  for_each (oset.begin(), oset.end(), printSet);
  cout << "---------------------------\n";
  cout << "interset contains: \n";
  for_each (interset.begin(), interset.end(), printSet);
  cout << "---------------------------\n";
*/
  cout << "are aset and interset equal? \n";
  if (aset.size() == interset.size()) {
    if (equal(aset.begin(),aset.end(),interset.begin())) {
      cout << "true\n";
      Tuple out;
      answer.addTuple(out);
    }
    else cout << "false\n";  
  }
  else cout << "false\n";
}

  } // namespace script
} // namespace dlvhex
