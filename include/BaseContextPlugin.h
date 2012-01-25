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
 * @file   BaseContextPlugin.h
 * @author Markus Boegl
 * @date   Sun Jan 24 13:26:52 2010
 * 
 * @brief  Base Context Plugin Element
 */
#ifndef _DLVHEX_MCSDIAGEXPL_BASECONTEXTPLUGIN_H
#define _DLVHEX_MCSDIAGEXPL_BASECONTEXTPLUGIN_H

#include "BaseContextAtom.h"
#include "ProgramCtxData.h"

#include <dlvhex2/PluginInterface.h>

namespace dlvhex {
namespace mcsdiagexpl {

// base class for plugins that implement MCS contexts for MCSIE
class BaseContextPlugin:
  public PluginInterface
{
public:
  BaseContextPlugin();
  virtual ~BaseContextPlugin();

  // User-Defined Atoms are registered in this Function
  // use the registerAtom<AtomType>(pcd); function below.
  virtual void registerAtoms(ProgramCtxData& pcd) const = 0;

  // plugin writers call this to register context atoms
  template<typename ContextAtomT>
  void registerAtom(ProgramCtxData& pcd) const
  {
    pcd.getContextAtoms().push_back(ContextAtomPtr(new ContextAtomT));
  };

  // overwrite this if you want to add more than only context atoms
  std::vector<PluginAtomPtr> createAtoms(ProgramCtx& ctx) const;
};

} // namespace mcsdiagexpl
} // namespace dlvhex

#endif // _DLVHEX_MCSDIAGEXPL_GENERICCONTEXTATOM_H

// vim:ts=8:
