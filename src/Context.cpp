#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "Context.h"

#include <climits>
#include <sstream>
#include <cstdlib>

#include <iostream>
#include <string>
#include <ostream>


namespace dlvhex {
  namespace mcsequilibrium {

   Context::Context(int num, std::string e, std::string p)
     : contextnum(num), extatom(e), param(p) {
   }//BridgeRuleEntry End

   Context::Context()
     : contextnum(0), extatom(""), param("") {
   }//BridgeRuleEntry End

   std::ostream&
   operator<< (std::ostream& out, const Context& context) {
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
