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
        GenericContextAtom(std::string name);
        void retrieve(const Query& query, Answer& answer) throw (PluginError);
	string getExtAtomName() { return hex_atom_name; };

	virtual set<string> acc(const string& param, const set<string>& input) = 0;

      protected:
        void convertAtomSetToStringSet(AtomSet& as, set<string>& sset);
	void convertQueryToStringSets(const Query& query, set<string>& aset, set<string>& bset, set<string>& oset) throw (PluginError);
	void stringset_intersection(const set<string>& aset, const set<string>& bset, set<string>& result);

      private:
	string hex_atom_name;
    };

  } // namespace mcsequilibrium
} // namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUM_GENERICCONTEXTATOM_H
