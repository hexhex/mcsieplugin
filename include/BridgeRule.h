#ifndef _DLVHEX_MCSEQUILIBRIUM_BRIDGERULE_H_
#define _DLVHEX_MCSEQUILIBRIUM_BRIDGERULE_H_

#include "BridgeRuleEntry.h"
#include <vector>
#include <string>

namespace dlvhex {
  namespace mcsequilibrium {

    class BridgeRule {
      public:
        BridgeRule();
        virtual void setHeadRule(int id, std::string f);
	virtual void addBodyRule(int id, std::string f, bool n);
	virtual void writeProgram(std::ostream& o);
	virtual void writeDebugProgram();


        BridgeRuleEntry Head() const { return head; }
        std::vector<BridgeRuleEntry> Body() const { return body; }

//        static std::vector<BridgeRuleEntry> body;
//	BridgeRuleEntry head;
      private:
        BridgeRuleEntry head;
	std::vector<BridgeRuleEntry> body;


    }; // END class BridgeRule

    std::ostream&
    operator<< (std::ostream&, const BridgeRule&);

  }  // END namespace mcsequilibrium
} // END namespace dlvhex
#endif // _DLVHEX_BRIDGERULE_H
