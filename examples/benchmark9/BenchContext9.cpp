#include "ContextAtom.h"
#include "ContextPlugin.h"

DLVHEX_MCSEQUILIBRIUM_PLUGIN(BenchmarkPlugin9,0,1,0)

namespace
{
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext1,"benchcontext9_context_acc1")

  std::set<std::set<std::string> > BenchContext1::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    if ((input.find("a") != input.end()) && (input.find("b") != input.end())) {
      return ret;
    }
    if (input.find("b") != input.end()) {
	s.insert("b");
    }
    if (input.find("a") != input.end()) {
	s.insert("a");
	s.insert("-b");
    }
    ret.insert(s);
    return ret;
  }

  void BenchmarkPlugin9::registerAtoms() {
    registerAtom<BenchContext1>();
  }
}
