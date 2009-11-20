#ifndef _DLVHEX_MCSEQUILIBRIUMBRIDGERULE_H_
#define _DLVHEX_MCSEQUILIBRIUMBRIDGERULE_H_

#include "MCSequilibriumBridgeRuleEntry.h"
#include <vector>
#include <string>
#include <set>

namespace dlvhex {
  namespace mcsequilibrium {

    class MCSequilibriumBridgeRule {
      public:
        MCSequilibriumBridgeRule();
        virtual void setHeadRule(int id, std::string f);
	virtual void addBodyRule(int id, std::string f, bool n);
	virtual void writeProgram(std::ostream& o);
	virtual void writeDebugProgram();


        MCSequilibriumBridgeRuleEntry Head() const { return head; }
        std::vector<MCSequilibriumBridgeRuleEntry> Body() const { return body; }

//        static std::vector<BridgeRuleEntry> body;
//	BridgeRuleEntry head;
      private:
        MCSequilibriumBridgeRuleEntry head;
	std::vector<MCSequilibriumBridgeRuleEntry> body;


    }; // END class MCSequilibriumBridgeRule

    std::ostream&
    operator<< (std::ostream&, const MCSequilibriumBridgeRule&);

  }  // END namespace mcsequilibrium
} // END namespace dlvhex
#endif // _DLVHEX_MCSEQUILIBRIUMBRIDGERULE_H
