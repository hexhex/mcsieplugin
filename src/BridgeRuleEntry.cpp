#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "BridgeRuleEntry.h"
#include <ostream>

namespace dlvhex {
  namespace mcsequilibrium {

   BridgeRuleEntry::BridgeRuleEntry(int id, std::string f, bool n)
    : contextid(id), fact(f), neg(n) {
   }//BridgeRuleEntry End

   BridgeRuleEntry::BridgeRuleEntry()
     : contextid(0), fact(""), neg(false) {
   }//BridgeRuleEntry End

   std::ostream&
   operator<< (std::ostream& out, const BridgeRuleEntry& ruleentry) {
     out << ruleentry.ContextID() << "(" << ruleentry.Fact() << ")";
     return out;
   }

  } // namespace script
} // namespace dlvhex
