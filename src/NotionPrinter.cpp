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
 * @file     NotionPrinter.cpp
 * @author   Peter Schueller
 * 
 * @brief    Helper to print pairs of sets represented in answer sets.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "NotionPrinter.h"

#include <dlvhex2/Registry.h>

#include <boost/tuple/tuple.hpp>

namespace dlvhex {
namespace mcsdiagexpl {

NotionPrinter::NotionPrinter(
		ProgramCtxData& pcd, ID id1, ID id2, PredicateMask& mask):
	pcd(pcd), id1(id1), id2(id2), mask(mask)
{
}
void NotionPrinter::
print(std::ostream& o, AnswerSetPtr model)
{
	mask.updateMask();
	InterpretationPtr projected(new Interpretation(pcd.reg));
	projected->getStorage() = model->interpretation->getStorage() & mask.mask()->getStorage();
	Interpretation::TrueBitIterator it, it_end;
	// use sets to have the result sorted
	std::set<std::string> comp1, comp2;
	for(boost::tie(it, it_end) = projected->trueBits();
			it != it_end; ++it)
	{
		const OrdinaryAtom& ogatom = pcd.reg->ogatoms.getByAddress(*it);
		assert(ogatom.tuple.size() == 2);
		const std::string& symbol = pcd.reg->getTermStringByID(ogatom.tuple[1]);
		if( ogatom.tuple[0] == id1 )
		{
			comp1.insert(symbol);
		}
		else
		{
			assert(ogatom.tuple[0] == id2);
			comp2.insert(symbol);
		}
	}
	o << "(" << printrange(comp1,"{",",","}") << "," << printrange(comp2,"{",",","}") << ")";
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=2:sw=2:
