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
 * @file   	CtxData.cpp
 * @author 	Markus Boegl
 * @author 	Peter Schueller
 * 
 * @brief       storage of plugin configuration and mcs representation
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "ProgramCtxData.h"

namespace dlvhex
{
namespace mcsdiagexpl
{

MCSIE::CtxData::CtxData():
  // whether plugin is enabled
  enabled(false),
  // how to calculate
  mode(EQREWRITING),
  // what to display/calculate
  diagnose(false),
  explanation(false),
  mindiag(false),
  minexpl(false),
  // whether to include output projected equilibria in output
  printopeq(true)
{
}

MCSIE::CtxData::~CtxData()
{
}

void MCSIE::CtxData::setEnabled()
{
  enabled = true;
}

void
MCSIE::CtxData::setDiag(){
        diagnose = true;
}

void
MCSIE::CtxData::setminDiag(){
        mindiag = true;
}

void
MCSIE::CtxData::setExp(){
        explanation = true;
}

void
MCSIE::CtxData::setminExp(){
        minexpl = true;
}

void
MCSIE::CtxData::setprintOPEQ(bool to) {
        printopeq = to;
}

void
MCSIE::CtxData::setMode(Mode to) {
  assert(to == DIAGREWRITING ||
         to == EXPLREWRITING ||
         to == EQREWRITING);
  mode = to;
}

} // namespace mcsdiagexpl
} // namespace dlvhex


