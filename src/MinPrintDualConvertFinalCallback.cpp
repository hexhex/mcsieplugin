/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2009,2010  Markus Boegl
 * Copyright (C) 2010,2011  Gerald Weidinger
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
 * @file   MinPrintDualConvertFinalCallback.cpp
 * @author Peter Schueller
 * 
 * @brief  Final callback for MCSIE (prints minimal notions, converts to dual notion)
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MinPrintDualConvertFinalCallback.h"

#include <cassert>

namespace dlvhex {
namespace mcsdiagexpl {

MinPrintDualConvertFinalCallback::
MinPrintDualConvertFinalCallback(ProgramCtxData& pcd):
	pcd(pcd)
{
}

void MinPrintDualConvertFinalCallback::
operator()()
{
	assert(false && "MinPrintDualConvertFinalCallback::operator()() not implemented");
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=2:sw=2:
