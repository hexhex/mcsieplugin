/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2010  Antonius Weinzierl
 * Copyright (C) 2012  Peter Schueller
 * 
 * This file is part of dlvhex-mcs-equilibrium-plugin.
 *
 * dlvhex-mcs-equilibrium-plugin is free software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * dlvhex-mcs-equilibrium-plugin is distributed in the hope that it will
 *  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dlvhex-dlplugin; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
 * @file   SaturationMetaAtom.h
 * @author Antonius Weinzierl
 * @author Peter Schueller
 * 
 * @brief  Meta atom for saturation encoding, can query other external atoms
 */
#ifndef _DLVHEX_MCSDIAGEXPL_SATURATION_META_ATOM_H
#define _DLVHEX_MCSDIAGEXPL_SATURATION_META_ATOM_H

#include "ProgramCtxData.h"

#include <dlvhex2/PluginInterface.h>

namespace dlvhex {
    namespace mcsdiagexpl {
	
	class SaturationMetaAtom : public PluginAtom {
	    
	public:
	    SaturationMetaAtom(ProgramCtxData& pcd);

	    void retrieve(const Query& query, Answer& answer);

        protected:
            ProgramCtxData& pcd;
	};
	
  } // namespace mcsdiagexpl
} // namespace dlvhex

#endif // _DLVHEX_MCSDIAGEXPL_SATURATION_META_ATOM_H
// vim:ts=8:
