#ifndef _DLVHEX_MCSEQUILIBRIUM_CONTEXT_H_
#define _DLVHEX_MCSEQUILIBRIUM_CONTEXT_H_

#include <string>

namespace dlvhex {
  namespace mcsequilibrium {

      class Context {
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

      }; // END class Context

        std::ostream&
        operator<< (std::ostream&, const Context&);

  }  // END namespace mcsequilibrium
} // END namespace dlvhex
#endif // _DLVHEX_MCSEQUILIBRIUMCONTEXT_H
