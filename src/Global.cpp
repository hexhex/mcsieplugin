/*
 * Global.cpp
 *
 *  Created on: 02.04.2010
 *      Author: max
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "Global.h"

namespace dlvhex {
  namespace mcsdiagexpl {

	Global* Global::g = NULL;

	Global*
	Global::getInstance() {
		if (g == NULL) {
		  g = new Global();
		}
		return g;
	}

	void
	Global::setDiag(){
		explaination = false;
		diagnose = true;
	}

	void
	Global::setExp(){
		diagnose=false;
		explaination = true;
	}

	void
	Global::setMin() {
		if (diagnose || explaination)
			minimal = true;
	}


	void
	Global::setnoprintopeq() {
		noprintopeq = true;
	}

	bool
	Global::isnoprintopeq() {
		return noprintopeq;
	}

	bool
	Global::isDiag() {
		return diagnose;
	}

	bool
	Global::isExp() {
		return explaination;
	}

	bool
	Global::isMin() {
		return minimal;
	}

	bool
	Global::isSet() {
		return diagnose || explaination || minimal;
	}

  }
}


