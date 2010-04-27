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
			Global() : diagnose(false), explaination(false), minimal(false), noprintopeq(false) {};
			~Global() {};
			static Global* getInstance();
			void setDiag();
			void setExp();
			void setMin();
			void setnoprintopeq();
			bool isDiag();
			bool isExp();
			bool isMin();
			bool isnoprintopeq();
			bool isSet();

	  private:
			static Global *g;
			bool diagnose, explaination, minimal, noprintopeq;
	  };
  }
}

#endif /* _DLVHEX_MCSDIAGEXPL_GLOBAL_H_ */
