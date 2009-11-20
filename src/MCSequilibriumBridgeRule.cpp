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
	//std::cout << "add entry in vector: id: " << id << " fact: " << f << " neg: " << n << std::endl;
     MCSequilibriumBridgeRuleEntry elem = MCSequilibriumBridgeRuleEntry(id,f,n);
	//std::cout << "elem entry: " << elem.ContextID() << " fact: " << elem.Fact() << " neg: " << elem.Neg() << std::endl;
     body.push_back(elem);

/*     std::cout << "After inserting one element there are these elements in list: " << std::endl;
     for (std::vector<MCSequilibriumBridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
       MCSequilibriumBridgeRuleEntry elem = *it;
	std::cout << "elem entry: " << elem.ContextID() << " fact: " << elem.Fact() << " neg: " << elem.Neg() << std::endl;
     }
*/
   } // end of MCSequilibriumBridgeRule::addBodyRule

   void 
   MCSequilibriumBridgeRule::writeProgram(std::ostream& o) {
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
     for (std::vector<MCSequilibriumBridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
       MCSequilibriumBridgeRuleEntry elem = *it;
       o << "a" << elem << " v na" << elem << "." << std::endl;
       o << "o" << elem.ContextID() << "(X) :- a" << elem.ContextID() << "(X)." << std::endl;
       o << "o" << elem.ContextID() << "(X) :- na" << elem.ContextID() << "(X)." << std::endl;
     }
   }

   void 
   MCSequilibriumBridgeRule::writeDebugProgram() {
     std::cout << "MCSequilibriumBridgeRule DEBUG\n";
     std::cout << "there are " << body.size() << " elements in the body. \n";
     writeProgram(std::cout);
   }

   std::ostream&
   operator<< (std::ostream& out, const MCSequilibriumBridgeRule& rule) {
     // write bridgerule in asp form
    out << "b" << rule.Head() << " :- ";
     for (std::vector<MCSequilibriumBridgeRuleEntry>::iterator it = rule.Body().begin(); it != rule.Body().end(); ++it) {
       MCSequilibriumBridgeRuleEntry elem = *it;
       if (elem.Neg())
         out << "n";
       out << "a" << elem;
       if (it+1 != rule.Body().end())
         out << ", ";
       else
         out << "." << std::endl;
     }
     return out;
   }

  } // namespace script
} // namespace dlvhex
