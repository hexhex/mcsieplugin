#if !defined(_DLVHEX_MCSEQUILIBRIUM_GENERICCONTEXTATOM_H)
#define _DLVHEX_MCSEQUILIBRIUM_GENERICCONTEXTATOM_H

#include <dlvhex/PluginInterface.h>
#include <dlvhex/Error.h>
#include <set>
#include <string>

using namespace std;

namespace dlvhex {
  namespace mcsequilibrium {

    class GenericContextAtom : public PluginAtom {

      public:
        GenericContextAtom(std::string hex_atom);

        void retrieve(const Query& query, Answer& answer) throw (PluginError);
	//virtual set<set<string> > acc(const string& param, const set<string>& input) = 0;

      private:
        void convertStringSet(AtomSet& as, set<string>& sset);
    };

  } // namespace mcsequilibrium
} // namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUM_GENERICCONTEXTATOM_H
