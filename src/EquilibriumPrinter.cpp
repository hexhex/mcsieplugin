/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2009,2010  Markus Boegl
 * Copyright (C) 2010,2011  Gerald Weidinger
 * 
 * This file is part of dlvhex-mcs-equilibrium-plugin.
 *
 * dlvhex-mcs-equilibrium-plugin is free software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * dlvhex-mcs-equilibrium-plugin is distributed in the hope that it will
 *  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dlvhex-dlplugin; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


/**
 * @file     EquilibriumPrinter.cpp
 * @author   Peter Schueller
 * 
 * @brief    Helper to print pairs of sets represented in answer sets.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "EquilibriumPrinter.h"

#include <dlvhex2/Registry.h>

#include <boost/tuple/tuple.hpp>

namespace dlvhex {
namespace mcsdiagexpl {

EquilibriumPrinter::EquilibriumPrinter(
		ProgramCtxData& pcd):
	pcd(pcd)
{
}

void EquilibriumPrinter::
print(std::ostream& o, InterpretationPtr model)
{
	typedef std::list<PredicateMask>::iterator PredicateMaskIterator;

	MCS& mcs = pcd.mcs();

	o << "(";
	ContextIterator itc;
	PredicateMaskIterator itm;
	for(itc = mcs.contexts.begin(), itm = pcd.obmasks.begin();
			itc != mcs.contexts.end(), itm != pcd.obmasks.end();
			++itc, ++itm)
	{
		itm->updateMask();

		InterpretationPtr projected(new Interpretation(pcd.reg));
		projected->getStorage() = model->getStorage() & itm->mask()->getStorage();
		Interpretation::TrueBitIterator it, it_end;

		// use sets to have the result sorted
		std::set<std::string> beliefs;
		for(boost::tie(it, it_end) = projected->trueBits();
				it != it_end; ++it)
		{
			const OrdinaryAtom& ogatom = pcd.reg->ogatoms.getByAddress(*it);
			assert(ogatom.tuple.size() == 2);
			const std::string& symbol = pcd.reg->getTermStringByID(ogatom.tuple[1]);
			beliefs.insert(symbol);
		}

		if( itc != mcs.contexts.begin() )
			o << ",";
		o << printrange(beliefs,"{",",","}");
	}
	o << ")";
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=2:sw=2:
