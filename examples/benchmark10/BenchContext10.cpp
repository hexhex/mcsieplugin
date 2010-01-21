#include "ContextAtom.h"
#include "ContextPlugin.h"

DLVHEX_MCSEQUILIBRIUM_PLUGIN(BenchmarkPlugin10,0,1,0)

namespace
{
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext1,"benchcontext10_context_acc1")

  std::set<std::set<std::string> > BenchContext1::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    if ((input.find("b") == input.end()) && (input.find("e") != input.end())) {
	if (input.find("a") == input.end()) {
	  return ret;
	}
    }
    std::set<std::string> s;
    if (input.find("a") != input.end()) {
      s.insert("a");
      s.insert("b");
    }
    for (std::set<std::string>::iterator it = input.begin(); it != input.end(); it++) {
	if (s.find(*it) == s.end()) {
	  s.insert(*it);
	}
    }
    ret.insert(s);
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext2,"benchcontext10_context_acc2")

  std::set<std::set<std::string> > BenchContext2::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    if (input.find("c") != input.end()) {
	s.insert("c");
	s.insert("d");
    }
    for (std::set<std::string>::iterator it = input.begin(); it != input.end(); it++) {
	if (s.find(*it) == s.end()) {
	  s.insert(*it);
	}
    }
    ret.insert(s);
    return ret;
  }

  void BenchmarkPlugin10::registerAtoms() {
    registerAtom<BenchContext1>();
    registerAtom<BenchContext2>();
  }
}
