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

namespace dlvhex {
  namespace mcsdiagexpl {
	  class Global {
	  public:
			Global() : diagnose(false), explaination(false), mindiag(false), minexpl(false), noprintopeq(false) {};
			~Global() {};
			static Global* getInstance();
			void init();
			void setDiag();
			void setminDiag();
			void setExp();
			void setminExp();
			void setnoprintopeq();
			bool isDiag();
			bool isminDiag();
			bool isExp();
			bool isminExp();
			bool isnoprintopeq();
			bool isSet();

	  private:
			static Global *g;
			bool diagnose, explaination, mindiag, minexpl, noprintopeq;
	  };
  }
}

#endif /* _DLVHEX_MCSDIAGEXPL_GLOBAL_H_ */
