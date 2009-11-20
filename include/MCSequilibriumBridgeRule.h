#ifndef _DLVHEX_MCSEQUILIBRIUMBRIDGERULE_H_
#define _DLVHEX_MCSEQUILIBRIUMBRIDGERULE_H_

#include "MCSequilibriumBridgeRuleEntry.h"
#include <vector>
#include <string>

namespace dlvhex {
  namespace mcsequilibrium {

    class MCSequilibriumBridgeRule {
      public:
        MCSequilibriumBridgeRule();
        virtual void setHeadRule(int id, std::string f);
	virtual void addBodyRule(int id, std::string f, bool n);
	virtual void writeProgram(std::ostream& o);
	virtual void writeDebugProgram();

//        static std::vector<BridgeRuleEntry> body;
//	BridgeRuleEntry head;
      private:
        MCSequilibriumBridgeRuleEntry head;
	std::vector<MCSequilibriumBridgeRuleEntry> body;

    }; // END class MCSequilibriumBridgeRule

  }  // END namespace mcsequilibrium
} // END namespace dlvhex
#endif // _DLVHEX_MCSEQUILIBRIUMBRIDGERULE_H
