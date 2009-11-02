/* -*- C++ -*- */

/**
 * @file   MCSEquilibriumAtom.h
 * @author Markus Boegl
 * @date   October 2009
 *
 * @brief  Equilibrium evaluation for Multi Context Systems in DLVHEX
 */

#if !defined(_DLVHEX_MCSEQUILIBRIUMATOM_H)
#define _DLVHEX_MCSEQUILIBRIUMATOM_H

#include <dlvhex/PluginInterface.h>
#include <dlvhex/Error.h>

namespace dlvhex {
  namespace mcsequilibrium {

	class MCSequilibriumAtom : public PluginAtom {
	public:
    		MCSequilibriumAtom();

		void retrieve(const Query& query, Answer& answer) throw (PluginError);
	};

  } // namespace mcsequilibrium
} // namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUMATOM_H
