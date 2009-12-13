#ifndef _DLVHEX_MCSEQUILIBRIUM_EQUILIBRIUMPRINTVISITOR_H
#define _DLVHEX_MCSEQUILIBRIUM_EQUILIBRIUMPRINTVISITOR_H

#include "dlvhex/PrintVisitor.h"
#include <iosfwd>

namespace dlvhex {
  namespace mcsequilibrium {

    class EquilibriumPrintVisitor : public RawPrintVisitor {
      public:
        explicit
        EquilibriumPrintVisitor(std::ostream&);

        /// outputs the Equilibrium in '{(a,b,c), (cd,bx)}' form
        virtual void
        visit(AtomSet* const);
    };
  } // END namespace mcsequilibrium
} // END namespace dlvhex

#endif /* _DLVHEX_EQUILIBRIUMOUTPUTBUILDER_H */


// Local Variables:
// mode: C++
// End:
