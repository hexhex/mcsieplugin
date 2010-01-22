#include "ContextInterfaceAtom.h"
#include "ContextInterfacePlugin.h"

DLVHEX_MCSEQUILIBRIUM_PLUGIN(TestPlugin3,0,1,0)

namespace
{//test_context1
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(TestContext1,"testcontext3_context_acc1")

  std::set<std::set<std::string> > TestContext1::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    if ((input.find("foo") != input.end()) && (input.find("bar") != input.end())) {
      s.insert("foo");
      //s.insert("bar");
      ret.insert(s);
      return ret;
    }
    if ((input.find("foo") != input.end()) && (input.find("bar") == input.end())) {
      s.insert("foo");
      ret.insert(s);
      return ret;
    }
    if ((input.find("foo") == input.end()) && (input.find("bar") != input.end())) {
      s.insert("bar");
      ret.insert(s);
      return ret;
    }
    if ((input.find("foo") == input.end()) && (input.find("bar") == input.end())) {
      s.insert("foo");
      ret.insert(s);
      s.clear();
      //s.insert("bar");
      ret.insert(s);
    }
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(TestContext2,"testcontext3_context_acc2")

  std::set<std::set<std::string> > TestContext2::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    if (input.find("fee") != input.end()) {
      s.insert("fee");
      ret.insert(s);
    } 
    return ret;
  }

  void TestPlugin3::registerAtoms() {
    registerAtom<TestContext1>();
    registerAtom<TestContext2>();
  }

}
