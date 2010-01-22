#include "ContextInterfaceAtom.h"
#include "ContextInterfacePlugin.h"

DLVHEX_MCSEQUILIBRIUM_PLUGIN(BenchmarkPlugin7,0,1,0)

namespace
{
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext1,"benchcontext7_context_acc1")

  std::set<std::set<std::string> > BenchContext1::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    for (std::set<std::string>::iterator it = input.begin(); it != input.end(); it++) {
	std::set<std::string> s;
	if (s.find(*it) == s.end()) {
	  s.insert(*it);
	}
	ret.insert(s);
    }
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext2,"benchcontext7_context_acc2")

  std::set<std::set<std::string> > BenchContext2::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    for (std::set<std::string>::iterator it = input.begin(); it != input.end(); it++) {
	std::set<std::string> s;
	if (s.find(*it) == s.end()) {
	  s.insert(*it);
	}
	ret.insert(s);
    }
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext3,"benchcontext7_context_acc3")

  std::set<std::set<std::string> > BenchContext3::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    for (std::set<std::string>::iterator it = input.begin(); it != input.end(); it++) {
	std::set<std::string> s;
	if (s.find(*it) == s.end()) {
	  s.insert(*it);
	}
	ret.insert(s);
    }
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext4,"benchcontext7_context_acc4")

  std::set<std::set<std::string> > BenchContext4::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    if (input.find("d") == input.end()) {
      std::set<std::string> s;
      for (std::set<std::string>::iterator it = input.begin(); it != input.end(); it++) {
	  if (s.find(*it) == s.end()) {
	    s.insert(*it);
	  }
      }
      ret.insert(s);
    }
    return ret;
  }

  void BenchmarkPlugin7::registerAtoms() {
    registerAtom<BenchContext1>();
    registerAtom<BenchContext2>();
    registerAtom<BenchContext3>();
    registerAtom<BenchContext4>();
  }
}
