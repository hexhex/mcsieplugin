#include "ContextInterfaceAtom.h"
#include "ContextInterfacePlugin.h"

DLVHEX_MCSEQUILIBRIUM_PLUGIN(BenchmarkPlugin2,0,1,0)

namespace
{
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext1,"benchcontext2_context_acc0")

  std::set<std::set<std::string> > BenchContext1::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    s.insert("b");
    ret.insert(s);
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext2,"benchcontext2_context_acc1")

  std::set<std::set<std::string> > BenchContext2::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    s.insert("a");
    ret.insert(s);
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext3,"benchcontext2_context_acc2")

  std::set<std::set<std::string> > BenchContext3::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    if (input.find("c") == input.end()) {
      std::set<std::string> s;
      ret.insert(s);
    }
    return ret;
  }

  void BenchmarkPlugin2::registerAtoms() {
    registerAtom<BenchContext1>();
    registerAtom<BenchContext2>();
    registerAtom<BenchContext3>();
  }
}
