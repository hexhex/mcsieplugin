#ifndef _DLVHEX_MCSEQUILIBRIUM_PARSECONTEXT_H_
#define _DLVHEX_MCSEQUILIBRIUM_PARSECONTEXT_H_

#include <string>

namespace dlvhex {
  namespace mcsequilibrium {

      class ParseContext {
        private:
          int contextnum;
          std::string extatom;
          std::string param;

        public:
          ParseContext(int num, std::string e, std::string p);
          ParseContext();

          int ContextNum() const { return contextnum; }
          std::string ExtAtom() const { return extatom; }
          std::string Param() const { return param; }

      }; // END class Context

        std::ostream&
        operator<< (std::ostream&, const ParseContext&);

  }  // END namespace mcsequilibrium
} // END namespace dlvhex
#endif // _DLVHEX_MCSEQUILIBRIUMCONTEXT_H
