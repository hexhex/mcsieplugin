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
 * @file   ParseContext.cpp
 * @author Markus Boegl
 * @date   Sun Jan 24 13:46:27 2010
 * 
 * @brief  Context element for Parsing the Input file
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "ParseContext.h"
#include <ostream>


namespace dlvhex {
  namespace mcsdiagexpl {

   ParseContext::ParseContext(int num, std::string e, std::string p)
     : contextnum(num), extatom(e), param(p) {
   }//BridgeRuleEntry End

   ParseContext::ParseContext()
     : contextnum(0), extatom(""), param("") {
   }//BridgeRuleEntry End

   std::ostream&
   operator<< (std::ostream& out, const ParseContext& context) {
     out << ":- not &" << context.ExtAtom() 
       << "[" << context.ContextNum()
       << ",a" << context.ContextNum()
       << ",b" << context.ContextNum() 
       << ",o" << context.ContextNum()
       << ",\"" << context.Param() << "\"]()." << std::endl;
     return out;
   }

  } // namespace mcsdiagexpl
} // namespace dlvhex
