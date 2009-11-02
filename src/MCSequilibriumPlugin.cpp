/* -*- C++ -*- */

/**
 * @file   MCSEquilibriumPlugin.cpp
 * @author Markus Boegl
 * @date   October 2009
 *
 * @brief  Equilibrium evaluation for Multi Context Systems in DLVHEX
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSequilibriumPlugin.h"

#include <cstdlib>


namespace dlvhex {
  namespace mcsequilibrium {

MCSequilibriumPlugin::MCSequilibriumPlugin()
    : activatePlugin(1), mcseconverter(new MCSequilibriumConverter()) {
}


MCSequilibriumPlugin::~MCSequilibriumPlugin() {
    delete mcseconverter;
}


void
MCSequilibriumPlugin::getAtoms(AtomFunctionMap& a) {
  boost::shared_ptr<PluginAtom> mcsequi(new MCSequilibriumAtom);
  a["mcsequi"] = mcsequi;
}


void
MCSequilibriumPlugin::setOptions(bool doHelp, std::vector<std::string>& argv,
                         std::ostream& out) {

  
}


PluginConverter*
MCSequilibriumPlugin::createConverter() {
    if (!this->activatePlugin) {
        return 0;
    }

    return mcseconverter;
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
