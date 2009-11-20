#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSequilibriumBridgeRule.h"

#include <climits>
#include <sstream>
#include <cstdlib>

#include <iostream>
#include <string>
#include <ostream>
#include <vector>


namespace dlvhex {
  namespace mcsequilibrium {

  MCSequilibriumBridgeRule::MCSequilibriumBridgeRule() {
     // init
   }

   void
   MCSequilibriumBridgeRule::setHeadRule(int id, std::string f) {
     head = MCSequilibriumBridgeRuleEntry(id,f);
   } // end of MCSequilibriumBridgeRule::setHeadRule

   void
   MCSequilibriumBridgeRule::addBodyRule(int id, std::string f, bool n){
     body.push_back(MCSequilibriumBridgeRuleEntry(id,f,n));
   } // end of MCSequilibriumBridgeRule::addBodyRule


   void 
   MCSequilibriumBridgeRule::writeProgram(std::ostream& o) {
     o << "write my programm test\n";
     // write bridgerule in asp form
     o << "b" << head << " :- ";
     for (std::vector<MCSequilibriumBridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
       MCSequilibriumBridgeRuleEntry elem = *it;
       if (elem.Neg())
         o << "n";
       o << "a" << elem;
       if (it+1 != body.end())
         o << ", ";
       else
         o << "." << std::endl;
     }
   }

   void 
   MCSequilibriumBridgeRule::writeDebugProgram() {
     std::cout << "MCSequilibriumBridgeRule DEBUG\n";
     std::cout << "there are " << body.size() << " elements in the body. \n";
     writeProgram(std::cout);
   }


  } // namespace script
} // namespace dlvhex
