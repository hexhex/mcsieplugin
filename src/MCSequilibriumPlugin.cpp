#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSequilibriumPlugin.h"

namespace dlvhex {
  namespace mcsequilibrium {

MCSequilibriumPlugin::MCSequilibriumPlugin()
    : activatePlugin(1), mcseconverter(new Converter()), equilibriumOB(new EquilibriumOutputBuilder()) {
}


MCSequilibriumPlugin::~MCSequilibriumPlugin() {
    delete mcseconverter;
    // do not delete the equilibriumOB here because the
    // OutputBuilder will be deleted by dlvhex
    // and if you delete it here, there will be an error
}

void
MCSequilibriumPlugin::setupProgramCtx(dlvhex::ProgramCtx& pc) {
	pc.setOutputBuilder(equilibriumOB);
}

OutputBuilder*
MCSequilibriumPlugin::createOutputBuilder() {
   return equilibriumOB;
}


PluginConverter*
MCSequilibriumPlugin::createConverter() {
    if (!this->activatePlugin) {
        return 0;
    }
    return mcseconverter;
}

void 
MCSequilibriumPlugin::registerAtoms() {
   registerAtom<DLV_ASP_ContextAtom>();
}

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
