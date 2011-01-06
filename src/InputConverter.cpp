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
 * @file   Converter.cpp
 * @author Markus Boegl
 * @date   Sun Jan 24 13:34:29 2010
 * 
 * @brief  Converts the Input file
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "InputConverter.h"
#include "dlvhex/SpiritDebugging.h"
#include "BridgeRuleEntry.h"
#include "Global.h"
#include "InputConverterDiagnosis.h"
#include "InputConverterExplanations.h"


#include <iostream>
#include <sstream>

namespace dlvhex {
  namespace mcsdiagexpl {

	
   void
   InputConverter::convert(std::istream& i, std::ostream& o) {
     MCSdescriptionGrammar mcsdgram;
     std::ostringstream buf;
     buf << i.rdbuf();
     std::string input = buf.str();

     iterator_t it_begin = input.c_str();
     iterator_t it_end = input.c_str() + input.size();

     boost::spirit::classic::tree_parse_info<iterator_t, factory_t> info = 
       boost::spirit::classic::ast_parse<factory_t>(it_begin, it_end, mcsdgram, boost::spirit::classic::space_p);

     if (!info.full) {
       throw PluginError("MCS Equilibrium Plugin: Inputfile syntax error!");
     }

     // if there's not 1 tree in the result of the parser, this is a bug
     assert(info.trees.size() == 1);

     // Convert the Parse Tree to a asp program
     std::stringstream ss;
     if (!Global::getInstance()->isCalculationOverExplanations()){
	InputConverterDiagnosis::getInstance()->convertParseTreeToDLVProgram(*info.trees.begin(), ss);
     }else{
	InputConverterExplanations::getInstance()->convertParseTreeToDLVProgram(*info.trees.begin(), ss);	
     }
	ss << "e1(r1)." << std::endl;
	ss << "e1(r2)." << std::endl;
	ss << "e1(r4)." << std::endl;
	ss << "e2(r5).";
     }

	//guess a subset of the candidate explanation
	// for which holds that E1 C_ r1 C_ brM and r2 C_ brM \ E2
	//std::cout << "r1(R) :- e1(R)." << std::endl;
	//std::cout << "r1(R) v nr1(R) :− ne1(R)." << std::endl;
	//std::cout << "r2(R)vnr2(R) :− ne2(R)." << std::endl;
	// ensure saturation
	//std::cout << ":- not spoil." << std::endl;

	

	//std::cout << "==============================================" << std::endl;
	//std::cout << o.rdbuf();

     #ifdef DEBUG
       std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
       std::cout << "Converted DLV Program: " << std::endl;
       std::cout << ss.str();
       std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
     #endif
     o << ss.rdbuf();
	

   } // end of MCSequilibriumConverter::convert

  } // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
