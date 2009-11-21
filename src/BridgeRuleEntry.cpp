#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "BridgeRuleEntry.h"

#include <climits>
#include <sstream>
#include <cstdlib>

#include <iostream>
#include <string>
#include <ostream>


namespace dlvhex {
  namespace mcsequilibrium {

   BridgeRuleEntry::BridgeRuleEntry(int id, std::string f, bool n)
    : contextid(id), fact(f), neg(n) {

	/*contextid = 99;
	fact = "aaaaa";
        neg = true;*/
   }//BridgeRuleEntry End

   BridgeRuleEntry::BridgeRuleEntry()
     : contextid(0), fact(""), neg(false) {
      contextid=3333;
   }//BridgeRuleEntry End

   std::ostream&
   operator<< (std::ostream& out, const BridgeRuleEntry& ruleentry) {
     out << ruleentry.ContextID() << "(" << ruleentry.Fact() << ")";
     return out;
   }

  } // namespace script
} // namespace dlvhex
