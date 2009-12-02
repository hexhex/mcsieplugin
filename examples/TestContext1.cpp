#include "GenericContextAtom.h"

namespace TestNamespace
{

DLVHEX_MCSEQUILIBRIUM_CONTEXT(TestContext1,test_context1_acc)
DLVHEX_MCSEQUILIBRIUM_CONTEXT(TestContext2,test_context2_acc)

std::set<std::string> TestContext1::acc(
    const std::string& param, const std::set<std::string>& input)
{
  std::set<std::string> ret;
  // TODO
  return ret;
}

// TODO write TestContext2::acc

DLVHEX_MCSEQUILIBRIUM_PLUGIN(TestPlugin,0,1,0)

bool TestPlugin::registerContexts()
{
  registerContext<TestContext1>();
  registerContext<TestContext2>();
  return true;
}

}
