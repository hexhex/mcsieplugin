#include "ContextAtom.h"
#include "ContextPlugin.h"
#include <iostream>

namespace TestNamespace
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
    }
    s.clear();
    if (input.find("tweedy_is_penguin") != input.end()) {
      s.insert("tweedy_is_penguin");
    }
    ret.insert(s);
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
    //std::cout << "param: " << param << std::endl;
    if (param.find("ctx1",0) != std::string::npos) {
      std::set<std::string> s;
      s.insert("tweedy_is_dove");
      ret.insert(s);
      s.clear();
      s.insert("tweedy_is_penguin");
      ret.insert(s);
    }
    if (param.find("ctx2",0) != std::string::npos) {
      std::set<std::string> s;
      s.insert("can_fly");
      ret.insert(s);
      
    }
    if (param.find("ctx3",0) != std::string::npos) {
      std::set<std::string> s;
      s.insert("rescue");
      ret.insert(s);
    }
    ret.insert(input);
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_PLUGIN(TestPlugin,0,1,0)

  void
  TestPlugin::getAtoms(AtomFunctionMap& a) {
    boost::shared_ptr<dlvhex::mcsequilibrium::BaseContextAtom> test1(new TestContext1());
    a[(test1.get())->getExtAtomName()] = test1;
    boost::shared_ptr<dlvhex::mcsequilibrium::BaseContextAtom> test2(new TestContext2());
    a[(test2.get())->getExtAtomName()] = test2;
    boost::shared_ptr<dlvhex::mcsequilibrium::BaseContextAtom> test3(new TestContext3());
    a[(test3.get())->getExtAtomName()] = test3;
  }

  TestPlugin theTestPlugin;
}

extern "C"
TestNamespace::TestPlugin*
PLUGINIMPORTFUNCTION() {
  TestNamespace::theTestPlugin.setPluginName("TestPlugin1");
  TestNamespace::theTestPlugin.setVersion(0,0,1);

  return &TestNamespace::theTestPlugin;
}
