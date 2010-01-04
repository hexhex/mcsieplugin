#ifndef _DLVHEX_MCSEQUILIBRIUM_DLV_ASP_CONTEXTATOM_H
#define _DLVHEX_MCSEQUILIBRIUM_DLV_ASP_CONTEXTATOM_H

#include "BaseContextAtom.h"
#include <string>

namespace dlvhex {
  namespace mcsequilibrium {

    class DLV_ASP_ContextAtom : public BaseContextAtom {

      public:
        DLV_ASP_ContextAtom() : BaseContextAtom("dlv_asp_context_acc") {};
        void retrieve(const Query& query, Answer& answer) throw (PluginError);
    };

  } // namespace script
} // namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUM_DLV_ASP_CONTEXTATOM_H
