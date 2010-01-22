#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "BridgeRule.h"

#include <ostream>
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
     BridgeRuleEntry elem = BridgeRuleEntry(id,f,n);
     body.push_back(elem);
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
    } else {
	o << "b" << head << "." << std::endl;
    }
   }
  } // namespace script
} // namespace dlvhex
