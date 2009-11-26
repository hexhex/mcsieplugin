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
#include "GenericContextAtom.h"
#include "DLV_ASP_Context.h"

#include <cstdlib>

#include <iostream>


namespace dlvhex {
  namespace mcsequilibrium {

MCSequilibriumPlugin::MCSequilibriumPlugin()
    : activatePlugin(0), mcseconverter(new Converter()) {
}


MCSequilibriumPlugin::~MCSequilibriumPlugin() {
    delete mcseconverter;
}


void
MCSequilibriumPlugin::getAtoms(AtomFunctionMap& a) {
  //boost::shared_ptr<PluginAtom> mcsequi(new GenericContextAtom(""));
  //a["dlv_asp_context_acc"] = mcsequi;

  //GenericContextAtom *gca = new DLV_ASP_Context(""));
  //DLV_ASP_Context dlvc("");
  //GenericContextAtom *gca = &dlvc;

  boost::shared_ptr<GenericContextAtom> mcsequi(new DLV_ASP_Context());
  a[(mcsequi.get())->getExtAtomName()] = mcsequi;
}

void
MCSequilibriumPlugin::setupProgramCtx(dlvhex::ProgramCtx& pc) {
	//std::cout << "Seting up ProgrammContext!!!!!!!!!" << std::endl;
	//std::vector<dlvhex::PluginInterface*> *retv = pc.getPlugins();
	//pc.openPlugins();
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
