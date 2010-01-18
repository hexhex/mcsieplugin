#ifndef _DLVHEX_MCSEQUILIBRIUM_ACC_CONTEXTATOM_H
#define _DLVHEX_MCSEQUILIBRIUM_ACC_CONTEXTATOM_H

#include "BaseContextAtom.h"

namespace dlvhex {
  namespace mcsequilibrium {

    class ACC_ContextAtom : public BaseContextAtom {

      public:
        ACC_ContextAtom(std::string name): BaseContextAtom(name) {};
        virtual void 
	retrieve(const Query& query, Answer& answer) throw (PluginError);
	virtual std::set<std::set<std::string> > 
	acc(const std::string& param, const std::set<std::string>& input) = 0;
    };
  } // namespace mcsequilibrium
} // namespace dlvhex
#endif // _DLVHEX_MCSEQUILIBRIUM_GENERICCONTEXTATOM_H
