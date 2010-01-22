#ifndef _CONTEXTINTERFACEPLUGIN_H_
#define _CONTEXTINTERFACEPLUGIN_H_

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
#endif //_CONTEXTINTERFACEPLUGIN_H_
