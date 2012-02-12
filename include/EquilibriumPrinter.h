/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
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
 * @file   EquilibriumPrinter.h
 * @author Peter Schueller
 * 
 * @brief  Helper to print pairs of sets represented in answer sets.
 */
#ifndef _DLVHEX_MCSDIAGEXPL_EQUILIBRIUMPRINTER_H_
#define _DLVHEX_MCSDIAGEXPL_EQUILIBRIUMPRINTER_H_

#include "ProgramCtxData.h"

#include <dlvhex2/AnswerSet.h>

#include <ostream>

namespace dlvhex {
namespace mcsdiagexpl {

class EquilibriumPrinter
{
public:
	EquilibriumPrinter(ProgramCtxData& pcd);
  void print(std::ostream& o, AnswerSetPtr model);

protected:
	ProgramCtxData& pcd;
};

} // END namespace mcsdiagexpl
} // END namespace dlvhex

#endif // _DLVHEX_MCSDIAGEXPL_EQUILIBRIUMPRINTER_H_
