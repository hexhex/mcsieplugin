#include "ContextInterfaceAtom.h"
#include "ContextInterfacePlugin.h"

DLVHEX_MCSEQUILIBRIUM_PLUGIN(BenchmarkPlugin3,0,1,0)

namespace
{
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext1,"benchcontext3_context_acc1")

  std::set<std::set<std::string> > BenchContext1::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    s.insert("a");
    ret.insert(s);
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext2,"benchcontext3_context_acc2")

  std::set<std::set<std::string> > BenchContext2::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    if (input.find("b") == input.end()) {
      std::set<std::string> s;
      ret.insert(s);
    }
    return ret;
  }

  void BenchmarkPlugin3::registerAtoms() {
    registerAtom<BenchContext1>();
    registerAtom<BenchContext2>();
  }
}
