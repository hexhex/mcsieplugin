#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSequilibriumBridgeRuleEntry.h"

#include <climits>
#include <sstream>
#include <cstdlib>

#include <iostream>
#include <string>
#include <ostream>


namespace dlvhex {
  namespace mcsequilibrium {

   MCSequilibriumBridgeRuleEntry::MCSequilibriumBridgeRuleEntry(int id, std::string f, bool n)
     : contextid(id), fact(f), neg(n) {
   }//BridgeRuleEntry End

   MCSequilibriumBridgeRuleEntry::MCSequilibriumBridgeRuleEntry()
     : contextid(0), fact(""), neg(false) {
   }//BridgeRuleEntry End

   std::ostream&
   operator<< (std::ostream& out, const MCSequilibriumBridgeRuleEntry& ruleentry) {
     out << ruleentry.ContextID() << "(" << ruleentry.Fact() << ")";
     return out;
   }

  } // namespace script
} // namespace dlvhex
