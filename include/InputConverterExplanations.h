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
 * @file   QiConverter.h
 * @author Gerald Weidinger (refactored)
 * @date   Sun Dez 28 13:34:49 2010
 * 
 * @brief  Converts the Input file for the calculation over dignosis.
 */
#ifndef _DLVHEX_MCSDIAGEXPL_INPUTCONVERTEREXPLANATION_H_
#define _DLVHEX_MCSDIAGEXPL_INPUTCONVERTEREXPLANATION_H_

#include <dlvhex/PluginInterface.h>
#include "InputParserDriver.h"
#include "BridgeRule.h"
#include "ParseContext.h"
#include "InputConverterHelper.h"
#include "Global.h"

namespace dlvhex {
  namespace mcsdiagexpl {

    class InputConverterExplanations {
      public:
	InputConverterExplanations() {};
	static InputConverterExplanations* getInstance();
	typedef boost::spirit::classic::node_val_data_factory<> factory_t;
	typedef const char* iterator_t;
	typedef boost::spirit::classic::tree_match<iterator_t, factory_t>::node_t node_t;

	void convertParseTreeToDLVProgram(node_t& node, std::ostream& o);
      
      private:
	std::vector<BridgeRule> bridgerules;
	std::vector<ParseContext> context;
	static InputConverterExplanations *ice;
	void writeProgram(std::ostream& o, BridgeRule br);
	

    }; // END class InputConverter
  }  // END namespace mcsdiagexpl
} // END namespace dlvhex

#endif // _DLVHEX_MCSDIAGEXPL_INPUTCONVERTER_H
