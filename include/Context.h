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
 * @file   Context.h
 * @author Markus Boegl
 * @author Peter Schueller (refactored)
 * @date   Sun Jan 24 13:47:00 2010
 * 
 * @brief  Context element for Parsing the Input file
 */
#ifndef _DLVHEX_MCSDIAGEXPL_CONTEXT_H_
#define _DLVHEX_MCSDIAGEXPL_CONTEXT_H_

#include <dlvhex2/Printhelpers.h>

#include <string>

namespace dlvhex {
  namespace mcsdiagexpl {

      class Context:
        public ostream_printable<Context>
      {
        private:
          int contextnum;
          std::string extatom;
          std::string param;

        public:
          Context(int num, std::string e, std::string p);
          Context();

          int ContextNum() const { return contextnum; }
          std::string ExtAtom() const { return extatom; }
          std::string Param() const { return param; }

	  std::ostream& print(std::ostream&) const;
      }; // END class Context

  }  // END namespace mcsdiagexpl
} // END namespace dlvhex
#endif // _DLVHEX_MCSDIAGEXPL_CONTEXT_H_
