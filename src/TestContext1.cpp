#include "ContextAtom.h"

namespace TestNamespace
{
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(TestContext1,"test_context1")

  std::set<std::set<std::string> > TestContext1::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    // TODO
    return ret;
  }
}
