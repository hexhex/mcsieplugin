#include "ContextAtom.h"
#include "ContextPlugin.h"

DLVHEX_MCSEQUILIBRIUM_PLUGIN(TestPlugin1,0,1,0)

namespace
{//test_context1
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(TestContext1,"testcontext1_context_acc1")

  std::set<std::set<std::string> > TestContext1::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    if (input.find("tweedy_is_dove") != input.end()) {
      s.insert("tweedy_is_dove");
      if (input.find("tweedy_is_penguin") != input.end()) {
        s.insert("tweedy_is_penguin");
      }
      ret.insert(s);
    } else {
      s.clear();
      if (input.find("tweedy_is_penguin") != input.end()) {
        s.insert("tweedy_is_penguin");
      }
      ret.insert(s);
    }
    if ((input.find("tweedy_is_dove") == input.end()) && (input.find("tweedy_is_penguin") == input.end())) {
      s.clear();
      s.insert("tweedy_is_dove");
      ret.insert(s);
      s.clear();
      s.insert("tweedy_is_penguin");
      ret.insert(s);
    }
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(TestContext2,"testcontext1_context_acc2")

  std::set<std::set<std::string> > TestContext2::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    if ((input.find("bird") != input.end()) && (input.find("penguin") == input.end())) {
       s.insert("can_fly");
    }
    ret.insert(s);
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(TestContext3,"testcontext1_context_acc3")

  std::set<std::set<std::string> > TestContext3::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    if (input.find("needs_rescue") != input.end()) {
      if (input.find("rescue") != input.end()) {
        s.insert("needs_rescue");
        s.insert("rescue");
        ret.insert(s);
      } else {
         //return 0;
      }
    } else {
      if (input.find("rescue") != input.end()) {
        s.insert("rescue");
      }
      ret.insert(s);
    }
    return ret;
  }

  void TestPlugin1::registerAtoms() {
    registerAtom<TestContext1>();
    registerAtom<TestContext2>();
    registerAtom<TestContext3>();
  }

}
