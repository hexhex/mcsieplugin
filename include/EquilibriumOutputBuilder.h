#ifndef _DLVHEX_MCSEQUILIBRIUM_EQUILIBRIUMOUTPUTBUILDER_H_
#define _DLVHEX_MCSEQUILIBRIUM_EQUILIBRIUMOUTPUTBUILDER_H_

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

      virtual void
      buildResult(std::ostream&, const ResultContainer&);
   };

  } // END namespace mcsequilibrium
} // END namespace dlvhex

#endif // _DLVHEX_EQUILIBRIUMOUTPUTBUILDER_H_