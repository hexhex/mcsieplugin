/* dlvhex-mcs-equilibrium-plugin -- Inconsistency analysis and equilibrium
 * semantics for heterogeneous nonmonotonic Multi-Context Systems in dlvhex.
 * Copyright (C) 2009,2010 Markus Boegl
 * Copyright (C) 2011 Gerald Weidinger
 * Copyright (C) 2012 Peter Schueller
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
 * @file   	InputConverter.h
 * @author 	Markus Boegl
 * @author 	Gerald Weidinger
 * @author 	Peter Schueller
 * @date   	Sun Feb 24 13:34:49 2011
 * 
 * @brief  Converts the Input file
 */
#ifndef _DLVHEX_MCSDIAGEXPL_INPUTCONVERTER_H_
#define _DLVHEX_MCSDIAGEXPL_INPUTCONVERTER_H_

#include <dlvhex2/PluginInterface.h>
#include "ProgramCtxData.h"

namespace dlvhex
{
namespace mcsdiagexpl
{

class InputConverter:
  public PluginConverter
{
public:
  InputConverter(ProgramCtxData& pcd);

  virtual void convert(std::istream& i, std::ostream& o);
protected:
  ProgramCtxData& pcd;
};

}
}

#endif // _DLVHEX_MCSDIAGEXPL_INPUTCONVERTER_H

// vi:ts=8:
