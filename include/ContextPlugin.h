#ifndef _CONTEXTPLUGIN_H
#define _CONTEXTPLUGIN_H

#include "MCSequilibriumPlugin.h"

#define DLVHEX_MCSEQUILIBRIUM_PLUGIN(classname,major,minor,micro) \
  class classname : public dlvhex::mcsequilibrium::MCSequilibriumPlugin {\
    public:\
      classname();\
      virtual void getAtoms(AtomFunctionMap&);\
  };\
  classname::classname(): dlvhex::mcsequilibrium::MCSequilibriumPlugin() {};\

#if 0
  classname thePlugin;\
\
  extern "C"\
  classname* PLUGINIMPORTFUNCTION() {\
    thePlugin.setPluginName(classname);\
    thePlugin.setVersion(major,minor,micro);\
\
    return &thePlugin;\
  }
#endif
#endif
