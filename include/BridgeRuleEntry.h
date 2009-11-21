#ifndef _DLVHEX_MCSEQUILIBRIUM_BRIDGERULEENTRY_H_
#define _DLVHEX_MCSEQUILIBRIUM_BRIDGERULEENTRY_H_

#include <vector>
#include <string>

namespace dlvhex {
  namespace mcsequilibrium {

      class BridgeRuleEntry {
        private:
          int contextid;
          std::string fact;
          bool neg;

        public:
          BridgeRuleEntry(int id, std::string f, bool n=false);
          BridgeRuleEntry();

          int ContextID() const { return contextid; }
          std::string Fact() const { return fact; }
          bool Neg() const { return neg; }

      }; // END class BridgeRuleEntry

        std::ostream&
        operator<< (std::ostream&, const BridgeRuleEntry&);

  }  // END namespace mcsequilibrium
} // END namespace dlvhex
#endif // _DLVHEX_MCSEQUILIBRIUM_BRIDGERULEENTRY_H
