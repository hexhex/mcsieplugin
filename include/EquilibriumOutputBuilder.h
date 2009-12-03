/* dlvhex -- Answer-Set Programming with external interfaces.
 * Copyright (C) 2007 Thomas Krennwallner
 * 
 * This file is part of dlvhex.
 *
 * dlvhex is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * dlvhex is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with dlvhex; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */


/**
 * @file   TextOutputBuilder.h
 * @author Thomas Krennwallner
 * @date   Mon Dec 22 20:52:26 CET 2007
 * 
 * @brief  Builder for standard text output.
 * 
 * 
 */

#ifndef _DLVHEX_MCSEQUILIBRIUM_EQUILIBRIUMOUTPUTBUILDER_H
#define _DLVHEX_MCSEQUILIBRIUM_EQUILIBRIUMOUTPUTBUILDER_H

#include "dlvhex/AnswerSet.h"
#include "dlvhex/OutputBuilder.h"

namespace dlvhex {
  namespace mcsequilibrium {


  class EquilibriumOutputBuilder : public OutputBuilder {

    public:
      /// Dtor
      virtual
      ~EquilibriumOutputBuilder();

      /// Ctor
      EquilibriumOutputBuilder();

      /**
       * @brief Build answer set.
       */
      virtual void
      buildResult(std::ostream&, const ResultContainer&);

};

  } // END namespace mcsequilibrium
} // END namespace dlvhex

#endif /* _DLVHEX_EQUILIBRIUMOUTPUTBUILDER_H */


// Local Variables:
// mode: C++
// End:
