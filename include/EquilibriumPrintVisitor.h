#ifndef _DLVHEX_MCSEQUILIBRIUM_EQUILIBRIUMPRINTVISITOR_H_
#define _DLVHEX_MCSEQUILIBRIUM_EQUILIBRIUMPRINTVISITOR_H_

#include "dlvhex/PrintVisitor.h"

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

#endif // _DLVHEX_MCSEQUILIBRIUM_EQUILIBRIUMPRINTVISITOR_H_
