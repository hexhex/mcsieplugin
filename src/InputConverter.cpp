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
  /*
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
    if (Global::getInstance()->isDiag()){
            //The calculation over explanations produces a superset of the actual diagnosis. some of the contained tuples may not be diagnosis.
            //If you want to print out the found superset remove this code, and enable the output code for diaagnosis in Outputrewriter.cpp
            std::cout << "A calculation over explanations cannot produce D, please choose an other value for parameter --ieexplain!" << std::endl;
            exit(0);
    }
    InputConverterExplanations::getInstance()->convertParseTreeToDLVProgram(*info.trees.begin(), ss);	
 }

 #ifdef DEBUG
   std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
   std::cout << "Converted DLV Program: " << std::endl;
   std::cout << ss.str();
   std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
 #endif
 o << ss.rdbuf();
    

   */
} // end of MCSequilibriumConverter::convert

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
