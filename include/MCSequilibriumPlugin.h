/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2009,2010  Markus Boegl
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
 * @file   MCSequilibriumPlugin.h
 * @author Markus Boegl
 * @date   Sun Jan 24 13:45:57 2010
 * 
 * @brief  Main Class of dlvhex-mcs-equilibrium-plugin
 */
#ifndef _DLVHEX_MCSEQUILIBRIUM_MCSEQUILIBRIUMPLUGIN_H_
#define _DLVHEX_MCSEQUILIBRIUM_MCSEQUILIBRIUMPLUGIN_H_

#include <dlvhex/ProgramCtx.h>
#include "Converter.h"
#include "EquilibriumOutputBuilder.h"
#include "DLV_ASP_ContextAtom.h"
#include "BaseContextPlugin.h"

namespace dlvhex {
  namespace mcsequilibrium {
	
    class MCSequilibriumPlugin : public BaseContextPlugin {
	private:
	  Converter* mcseconverter;
	  OutputBuilder* equilibriumOB;
	  MCSequilibriumPlugin(const MCSequilibriumPlugin&);
	  bool activatePlugin;
	  AtomFunctionMap *afm;

	public:
	  MCSequilibriumPlugin();
	  ~MCSequilibriumPlugin();
	  virtual void setupProgramCtx(ProgramCtx& pc);
	  virtual OutputBuilder* createOutputBuilder();
	  virtual PluginConverter* createConverter();
	  virtual void registerAtoms();
	
    }; // END class MCSequilibriumPlugin
  } // END namespace mcsequilibrium
} // END namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUM_MCSEQUILIBRIUMPLUGIN_H_