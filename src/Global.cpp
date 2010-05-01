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
		  //g->init();
		}
		return g;
	}

	void
	Global::init(){
		explaination = mindiag = minexpl = noprintopeq = diagnose = kr2010rewriting = false;
	}

	void
	Global::setDiag(){
		diagnose = true;
	}

	void
	Global::setminDiag(){
		mindiag = true;
	}

	void
	Global::setExp(){
		explaination = true;
	}

	void
	Global::setminExp(){
		minexpl = true;
	}

	void
	Global::setnoprintopeq() {
		noprintopeq = true;
	}

	void
	Global::setKR2010rewriting() {
		kr2010rewriting = true;
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
	Global::isminDiag() {
		return mindiag;
	}

	bool
	Global::isExp() {
		return explaination;
	}

	bool
	Global::isminExp() {
		return minexpl;
	}

	bool
	Global::isSet() {
		return explaination || diagnose || minexpl || mindiag;
	}

	bool
	Global::isKR2010rewriting() {
		return kr2010rewriting;
	}

  }
}


