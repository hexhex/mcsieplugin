#ifndef _DLVHEX_MCSEQUILIBRIUM_BASECONTEXTPLUGIN_H
#define _DLVHEX_MCSEQUILIBRIUM_BASECONTEXTPLUGIN_H

#include <dlvhex/PluginInterface.h>

namespace dlvhex {
  namespace mcsequilibrium {

    class BaseContextPlugin : public PluginInterface {
      private:
        AtomFunctionMap *a_int;

      public:
        BaseContextPlugin() {};

	template <class type> void registerAtom() {
           boost::shared_ptr<dlvhex::mcsequilibrium::BaseContextAtom> atom(new type());
           (*a_int)[(atom.get())->getExtAtomName()] = atom;
	};

	// User-Defined Atoms are registered in this Function
	// use the registerAtom<AtomType>(); function above.
	virtual void registerAtoms() = 0;

	void getAtoms(AtomFunctionMap& a) {
          a_int = &a;
	  registerAtoms();
	};
    };
  } // namespace mcsequilibrium
} // namespace dlvhex
#endif // _DLVHEX_MCSEQUILIBRIUM_GENERICCONTEXTATOM_H
