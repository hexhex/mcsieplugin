#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "BridgeRule.h"

#include <climits>
#include <sstream>
#include <cstdlib>

#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <list>


namespace dlvhex {
  namespace mcsequilibrium {

  BridgeRule::BridgeRule() {
     fact = false;
   }

  BridgeRule::BridgeRule(bool f) {
     fact = f;
   }

   void
   BridgeRule::setHeadRule(int id, std::string f) {
     head = BridgeRuleEntry(id,f);
   } // end of BridgeRule::setHeadRule

   void
   BridgeRule::addBodyRule(int id, std::string f, bool n){
	//std::cout << "add entry in vector: id: " << id << " fact: " << f << " neg: " << n << std::endl;
     BridgeRuleEntry elem = BridgeRuleEntry(id,f,n);
	//std::cout << "elem entry: " << elem.ContextID() << " fact: " << elem.Fact() << " neg: " << elem.Neg() << std::endl;
     body.push_back(elem);

/*     std::cout << "After inserting one element there are these elements in list: " << std::endl;
     for (std::vector<BridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
       BridgeRuleEntry elem = *it;
	std::cout << "elem entry: " << elem.ContextID() << " fact: " << elem.Fact() << " neg: " << elem.Neg() << std::endl;
     }
*/
   } // end of BridgeRule::addBodyRule

   void 
   BridgeRule::writeProgram(std::ostream& o) {
     // write bridgerule in asp form
     std::list<int> ilist;
     if (!fact) {
	     o << "b" << head << " :- ";
	     for (std::vector<BridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
	       BridgeRuleEntry elem = *it;
	       if (elem.Neg())
		 o << "n";
	       o << "a" << elem;
	       if (it+1 != body.end())
		 o << ", ";
	       else
		 o << "." << std::endl;
	     }
	     for (std::vector<BridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
	       BridgeRuleEntry elem = *it;
	       o << "a" << elem << " v na" << elem << "." << std::endl;
	       ilist.push_back(elem.ContextID());
	     }
	     ilist.unique();
	     ilist.sort();
	     for (std::list<int>::iterator it = ilist.begin(); it != ilist.end(); ++it) {
	       o << "o" << *it << "(X) :- a" << *it << "(X)." << std::endl;
	       o << "o" << *it << "(X) :- na" << *it << "(X)." << std::endl;
	     }
	     /*for (std::vector<BridgeRuleEntry>::iterator it = body.begin(); it != body.end(); ++it) {
	       BridgeRuleEntry elem = *it;
	       o << "o" << elem.ContextID() << "(X) :- a" << elem.ContextID() << "(X)." << std::endl;
	       o << "o" << elem.ContextID() << "(X) :- na" << elem.ContextID() << "(X)." << std::endl;
	     }*/
    } else {
	o << "b" << head << "." << std::endl;
    }
   }

   void 
   BridgeRule::writeDebugProgram() {
     std::cout << "BridgeRule DEBUG\n";
     std::cout << "there are " << body.size() << " elements in the body. \n";
     writeProgram(std::cout);
   }

   std::ostream&
   operator<< (std::ostream& out, const BridgeRule& rule) {
     // write bridgerule in asp form
    out << "b" << rule.Head() << " :- ";
     for (std::vector<BridgeRuleEntry>::iterator it = rule.Body().begin(); it != rule.Body().end(); ++it) {
       BridgeRuleEntry elem = *it;
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
