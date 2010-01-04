#include "ContextAtom.h"
#include "ContextPlugin.h"
#include <iostream>

namespace TestNamespace
{//test_context1
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(TestContext1,"dlv_asp")

  std::set<std::set<std::string> > TestContext1::acc(const std::string& param, const std::set<std::string>& input) {
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
    boost::shared_ptr<dlvhex::mcsequilibrium::BaseContextAtom> mcsequi(new TestContext1());
    a[(mcsequi.get())->getExtAtomName()] = mcsequi;
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
