#include "ContextAtom.h"
#include "ContextPlugin.h"

DLVHEX_MCSEQUILIBRIUM_PLUGIN(TestPlugin2,0,1,0)

namespace
{//test_context1
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(TestContext1,"testcontext2_context_acc1")

  std::set<std::set<std::string> > TestContext1::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    if (input.find("foo") != input.end()) {
      s.insert("foo");
      ret.insert(s);
    } 
    return ret;
  }

  void TestPlugin2::registerAtoms() {
    registerAtom<TestContext1>();
  }

}
