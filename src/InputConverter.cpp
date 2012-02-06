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
 * @file   	InputConverter.cpp
 * @author 	Markus Boegl
 * @author 	Gerad Weidinger
 * @author 	Peter Schueller
 * @date   	Sun Jan 08 13:34:29 2011
 * 
 * @brief       parses input into internal representation and creates rewritten program
 *
 * internal representation of MCS is in ProgramCtxData
 * configuration of rewriting is in ProgramCtxData
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "InputConverter.h"
#include <dlvhex2/Logger.h>
//#include "dlvhex/SpiritDebugging.h"
//#include "BridgeRuleEntry.h"
//#include "InputConverterDiagnosis.h"
//#include "InputConverterExplanations.h"

#include <iostream>
#include <sstream>

/*
namespace
{
  typedef boost::spirit::classic::node_val_data_factory<> factory_t;
  typedef const char* iterator_t;
  typedef boost::spirit::classic::tree_match<iterator_t, factory_t>::node_t node_t;
}
*/

namespace dlvhex
{

namespace mcsdiagexpl
{

InputConverter::InputConverter(ProgramCtxData& pcd):
  pcd(pcd)
{
}

/*
 * 1) parse input i into pcd
 * 2) rewrite representation in pcd to output o
 */
void InputConverter::convert(std::istream& i, std::ostream& o)
{
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
