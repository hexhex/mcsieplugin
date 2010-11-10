#ifndef _DLVHEX_MCSDIAGEXPL_SATURATION_META_ATOM_H
#define _DLVHEX_MCSDIAGEXPL_SATURATION_META_ATOM_H

#include "BaseContextAtom.h"

namespace dlvhex {
    namespace mcsdiagexpl {
	
	class SaturationMetaAtom : public PluginAtom {
	    
	public:
	    SaturationMetaAtom(): PluginAtom(false)
		{
		addInputConstant();
		addInputPredicate();
		addInputConstant();
		addInputPredicate();
		addInputPredicate();
		addInputPredicate();
		addInputConstant();
		setOutputArity(0);
	    }

	    void retrieve(const Query& query, Answer& answer) throw (PluginError);
	    
	
	};
	
  } // namespace mcsdiagexpl
} // namespace dlvhex

#endif // _DLVHEX_MCSDIAGEXPL_SATURATION_META_ATOM_H
