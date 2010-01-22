#ifndef _DLVHEX_MCSEQUILIBRIUM_BRIDGERULE_H_
#define _DLVHEX_MCSEQUILIBRIUM_BRIDGERULE_H_

#include "BridgeRuleEntry.h"
#include <vector>
#include <string>

namespace dlvhex {
  namespace mcsequilibrium {

    class BridgeRule {
      public:
	BridgeRule(bool f);
        BridgeRule();
        void setHeadRule(int id, std::string f);
	void addBodyRule(int id, std::string f, bool n);
	void writeProgram(std::ostream& o);

        BridgeRuleEntry Head() const { return head; }
        std::vector<BridgeRuleEntry> Body() const { return body; }

      private:
        BridgeRuleEntry head;
	std::vector<BridgeRuleEntry> body;
	bool fact;
    }; // END class BridgeRule
  }  // END namespace mcsequilibrium
} // END namespace dlvhex
#endif // _DLVHEX_MCSEQUILIBRIUM_BRIDGERULE_H_
