#ifndef _DLVHEX_MCSEQUILIBRIUMCONTEXT_H_
#define _DLVHEX_MCSEQUILIBRIUMCONTEXT_H_

#include <string>

namespace dlvhex {
  namespace mcsequilibrium {

      class MCSequilibriumContext {
        private:
          int contextnum;
          std::string extatom;
          std::string param;

        public:
          MCSequilibriumContext(int num, std::string e, std::string p);
          MCSequilibriumContext();

          int ContextNum() const { return contextnum; }
          std::string ExtAtom() const { return extatom; }
          std::string Param() const { return param; }

      }; // END class MCSequilibriumContext

        std::ostream&
        operator<< (std::ostream&, const MCSequilibriumContext&);

  }  // END namespace mcsequilibrium
} // END namespace dlvhex
#endif // _DLVHEX_MCSEQUILIBRIUMCONTEXT_H
