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
 * @file   BaseContextAtom.h
 * @author Markus Boegl
 * @author Peter Schueller
 * @date   Sun Jan 24 13:25:02 2010
 * 
 * @brief  Base Context Plugin Atom Element
 */
#ifndef _DLVHEX_MCSDIAGEXPL_BASECONTEXTATOM_H
#define _DLVHEX_MCSDIAGEXPL_BASECONTEXTATOM_H

#include "ProgramCtxData.h"

#include <dlvhex2/PluginInterface.h>

#include <boost/shared_ptr.hpp>

namespace dlvhex {
namespace mcsdiagexpl {

class BaseContextAtom:
  public PluginAtom
{
public:
  BaseContextAtom(std::string name, ProgramCtxData& pcd):
    PluginAtom(name, false),
    pcd(pcd)
  {
    addInputConstant();
    addInputPredicate();
    addInputPredicate();
    addInputPredicate();
    addInputConstant();
    setOutputArity(0);
  }

  virtual ~BaseContextAtom() { }

  virtual void retrieve(const Query& query, Answer& answer) = 0;

protected:
  typedef std::set<std::string> StringSet;
  virtual void convertQueryToStringSets(
      const Query& query,
      StringSet& aset, StringSet& bset, StringSet& oset);

  ProgramCtxData& pcd;
};
typedef boost::shared_ptr<BaseContextAtom>
        ContextAtomPtr;

} // namespace mcsdiagexpl
} // namespace dlvhex

#endif // _DLVHEX_MCSDIAGEXPL_BASECONTEXTATOM_H

// vim:ts=8:sw=2:
