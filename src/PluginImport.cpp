#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSequilibriumPlugin.h"

namespace dlvhex {
  namespace mcsequilibrium {

    MCSequilibriumPlugin theMCSequilibriumPlugin;

  } // namespace mcsequilibrium
} // namespace dlvhex

extern "C"
dlvhex::mcsequilibrium::MCSequilibriumPlugin*
PLUGINIMPORTFUNCTION() {
  dlvhex::mcsequilibrium::theMCSequilibriumPlugin.setPluginName(PACKAGE_TARNAME);
  dlvhex::mcsequilibrium::theMCSequilibriumPlugin.setVersion(MCSEQUILIBRIUMPLUGIN_MAJOR,
					     MCSEQUILIBRIUMPLUGIN_MINOR,
					     MCSEQUILIBRIUMPLUGIN_MICRO);

  return &dlvhex::mcsequilibrium::theMCSequilibriumPlugin;
}
