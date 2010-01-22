#ifndef _CONTEXTINTERFACEATOM_H_
#define _CONTEXTINTERFACEATOM_H_

#include "ACC_ContextAtom.h"

#define DLVHEX_MCSEQUILIBRIUM_CONTEXT(classname,funcname) \
  class classname : public dlvhex::mcsequilibrium::ACC_ContextAtom {\
    public:\
      classname();\
      virtual std::set<std::set<std::string> > acc(const std::string& param, const std::set<std::string>& input);\
  };\
  classname::classname(): ACC_ContextAtom(funcname) {};

#endif // _CONTEXTINTERFACEATOM_H_
