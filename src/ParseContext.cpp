#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "ParseContext.h"

#include <climits>
#include <sstream>
#include <cstdlib>

#include <iostream>
#include <string>
#include <ostream>


namespace dlvhex {
  namespace mcsequilibrium {

   ParseContext::ParseContext(int num, std::string e, std::string p)
     : contextnum(num), extatom(e), param(p) {
   }//BridgeRuleEntry End

   ParseContext::ParseContext()
     : contextnum(0), extatom(""), param("") {
   }//BridgeRuleEntry End

   std::ostream&
   operator<< (std::ostream& out, const ParseContext& context) {
     out << ":- not &" << context.ExtAtom() 
       << "[" << context.ContextNum()
       << ",a" << context.ContextNum()
       << ",b" << context.ContextNum() 
       << ",o" << context.ContextNum()
       << ",\"" << context.Param() << "\"]()." << std::endl;
     return out;
   }

  } // namespace script
} // namespace dlvhex
