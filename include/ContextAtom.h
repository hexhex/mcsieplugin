#ifndef _CONTEXTATOM_H
#define _CONTEXTATOM_H

#include "ACC_ContextAtom.h"

#define DLVHEX_MCSEQUILIBRIUM_CONTEXT(classname, funcname) \
  class classname : public ACC_ContextAtom {\
    public:\
      classname();\
      virtual std::set<std::set<std::string> > acc(const std::string& param, const std::set<std::string>& input);\
  };\
  classname::classname() {};
#endif
