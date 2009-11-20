#ifndef _DLVHEX_MCSEQUILIBRIUMBRIDGERULEENTRY_H_
#define _DLVHEX_MCSEQUILIBRIUMBRIDGERULEENTRY_H_

#include <vector>
#include <string>

namespace dlvhex {
  namespace mcsequilibrium {

      class MCSequilibriumBridgeRuleEntry {
        private:
          int contextid;
          std::string fact;
          bool neg;

        public:
          MCSequilibriumBridgeRuleEntry(int id, std::string f, bool n=false);
          MCSequilibriumBridgeRuleEntry();

          int ContextID() const { return contextid; }
          std::string Fact() const { return fact; }
          bool Neg() const { return neg; }

      }; // END class BridgeRuleEntry

        std::ostream&
        operator<< (std::ostream&, const MCSequilibriumBridgeRuleEntry&);

  }  // END namespace mcsequilibrium
} // END namespace dlvhex
#endif // _DLVHEX_MCSEQUILIBRIUMBRIDGERULE_H
