#include "ContextAtom.h"
#include "ContextPlugin.h"

DLVHEX_MCSEQUILIBRIUM_PLUGIN(BenchmarkPlugin4,0,1,0)

namespace
{
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext1,"benchcontext4_context_acc1")

  std::set<std::set<std::string> > BenchContext1::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    if (input.find("a") == input.end()) {
      std::set<std::string> s;
      ret.insert(s);
    }
    return ret;
  }

  void BenchmarkPlugin4::registerAtoms() {
    registerAtom<BenchContext1>();
  }
}
