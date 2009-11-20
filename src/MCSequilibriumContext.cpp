#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSequilibriumContext.h"

#include <climits>
#include <sstream>
#include <cstdlib>

#include <iostream>
#include <string>
#include <ostream>


namespace dlvhex {
  namespace mcsequilibrium {

   MCSequilibriumContext::MCSequilibriumContext(int num, std::string e, std::string p)
     : contextnum(num), extatom(e), param(p) {
   }//BridgeRuleEntry End

   MCSequilibriumContext::MCSequilibriumContext()
     : contextnum(0), extatom(""), param("") {
   }//BridgeRuleEntry End

   std::ostream&
   operator<< (std::ostream& out, const MCSequilibriumContext& context) {
     out << ":- not &" << context.ExtAtom() << "[a" << context.ContextNum()
       << ",b" << context.ContextNum() << ",o" << context.ContextNum()
       << ",\"" << context.Param() << "\"]()." << std::endl;
     return out;
   }

  } // namespace script
} // namespace dlvhex
