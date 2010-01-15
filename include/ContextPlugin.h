#ifndef _CONTEXTPLUGIN_H
#define _CONTEXTPLUGIN_H

#include "BaseContextPlugin.h"

#define DLVHEX_MCSEQUILIBRIUM_PLUGIN(classname,major,minor,micro) \
namespace {\
  class classname : public dlvhex::mcsequilibrium::BaseContextPlugin {\
    public:\
      classname();\
      virtual void registerAtoms();\
  };\
  classname::classname() {};\
  classname thePlugin;\
}\
\
  extern "C"\
  classname* PLUGINIMPORTFUNCTION() {\
    thePlugin.setPluginName(#classname);\
    thePlugin.setVersion(major,minor,micro);\
\
    return &thePlugin;\
  }
#endif
