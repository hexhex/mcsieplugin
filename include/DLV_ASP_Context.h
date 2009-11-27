#if !defined(_DLVHEX_MCSEQUILIBRIUM_DLV_ASP_CONTEXT_H)
#define _DLVHEX_MCSEQUILIBRIUM_DLV_ASP_CONTEXT_H

#include "GenericContextAtom.h"
#include <string>

using namespace std;

namespace dlvhex {
  namespace mcsequilibrium {

    class DLV_ASP_Context : public GenericContextAtom {

      public:
        DLV_ASP_Context();
        //void retrieve(const Query& query, Answer& answer) throw (PluginError);
	virtual set<string> acc(const string& param, const set<string>& input);
    };

  } // namespace script
} // namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUM_DLV_ASP_CONTEXT_H
