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
 * @file   MCSIEPlugin.h
 * @author Markus Boegl
 * @author Peter Schueller
 * @date   Sun Jan 24 13:45:57 2010
 * 
 * @brief  Main Class of dlvhex-mcs-equilibrium-plugin
 */
#ifndef _DLVHEX_MCSDIAGEXPL_MCSEQUILIBRIUMPLUGIN_H_
#define _DLVHEX_MCSDIAGEXPL_MCSEQUILIBRIUMPLUGIN_H_

//#include <dlvhex2/ProgramCtx.h>
//#include "InputConverter.h"
//#include "ProgramCtxData.h"
#include "BaseContextPlugin.h"
//#include "OutputRewriter.h"
//#include "DLV_ASP_ContextAtom.h"
//#include "Timing.h"
//#include "SaturationMetaAtom.h"

namespace dlvhex {
namespace mcsdiagexpl {
	
class MCSIEPlugin:
  public BaseContextPlugin
{
public:
  MCSIEPlugin();
  virtual ~MCSIEPlugin();

  virtual void registerAtoms(ProgramCtxData& pcd) const;
  // we do not only provide context atoms, so we also need to override the following
  virtual std::vector<PluginAtomPtr> createAtoms(ProgramCtx& ctx) const;

  virtual void printUsage(std::ostream& o) const;
  virtual void processOptions(std::list<const char*>& pluginOptions, ProgramCtx& ctx);
  virtual PluginConverterPtr createConverter(ProgramCtx&);

  // change model callback
  virtual void setupProgramCtx(ProgramCtx&);
};

} // END namespace mcsdiagexpl
} // END namespace dlvhex

#endif // _DLVHEX_MCSDIAGEXPL_MCSEQUILIBRIUMPLUGIN_H_

// vim:ts=8:
