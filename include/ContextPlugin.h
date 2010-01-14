#ifndef _CONTEXTPLUGIN_H
#define _CONTEXTPLUGIN_H

#include <dlvhex/PluginInterface.h>

#define DLVHEX_MCSEQUILIBRIUM_PLUGIN(classname,major,minor,micro) \
namespace {\
  class classname : public dlvhex::PluginInterface {\
    public:\
      classname();\
      virtual void getAtoms(AtomFunctionMap&);\
  };\
  classname::classname() {};\
  classname thePlugin;\
}\
\
  extern "C"\
  classname* PLUGINIMPORTFUNCTION() {\
    thePlugin.setPluginName(classname);\
    thePlugin.setVersion(major,minor,micro);\
\
    return &thePlugin;\
  }
#endif
