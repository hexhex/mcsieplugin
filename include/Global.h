/*
 * Global.h
 *
 *  Created on: 02.04.2010
 *      Author: max
 */

#ifndef _DLVHEX_MCSDIAGEXPL_GLOBAL_H_
#define _DLVHEX_MCSDIAGEXPL_GLOBAL_H_

#include <ostream>
#include <sstream>
#include <dlvhex/ProgramCtx.h>
#include <list>

namespace dlvhex {
  namespace mcsdiagexpl {
	  class Global {
	  public:
			Global() : diagnose(false), explanation(false), mindiag(false), minexpl(false), noprintopeq(false), kr2010rewriting(false), rewritingEnabled(false), calculationOverExplanations(false) {};
			~Global() {};
			static Global* getInstance();
			void init();
			void setDiag();
			void setminDiag();
			void setExp();
			void setminExp();
			void setnoprintopeq();
			void setKR2010rewriting();
			void setRewritingEnabled(bool value=true);
			void setCalculationOverExplanations();
			void setRuleList(std::list<std::string> rL);
			std::list<std::string> & getRuleList();
			bool isDiag();
			bool isminDiag();
			bool isExp();
			bool isminExp();
			bool isnoprintopeq();
			bool isSet();
			bool isKR2010rewriting();
			bool isRewritingEnabled();
			bool isCalculationOverExplanations();
			void setProgramCtx(ProgramCtx &pc);
			ProgramCtx* getProgramCtx();

	  private:
			static Global *g;
			ProgramCtx* pc;
			bool diagnose, explanation, mindiag, minexpl, noprintopeq, kr2010rewriting, rewritingEnabled, calculationOverExplanations;
			std::list<std::string> ruleList;
	  };
  }
}

#endif /* _DLVHEX_MCSDIAGEXPL_GLOBAL_H_ */
