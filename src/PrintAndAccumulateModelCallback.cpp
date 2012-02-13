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
 * @file   PrintAndAccumulateModelCallback.cpp
 * @author Peter Schueller
 * 
 * @brief  Model callback for MCSIE (print nonminimal notions, accumulate minimal ones)
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "PrintAndAccumulateModelCallback.h"

#include <dlvhex2/Interpretation.h>
#include <dlvhex2/AnswerSet.h>
#include <dlvhex2/Registry.h>

#include <ostream>

namespace dlvhex {
namespace mcsdiagexpl {

PrintAndAccumulateModelCallback::
PrintAndAccumulateModelCallback(ProgramCtxData& pcd):
  pcd(pcd),
  printanything(pcd.isDiag() || pcd.isExp() ||
                pcd.getMode() == ProgramCtxData::EQREWRITING),
  printnotion(pcd.isDiag() || pcd.isExp()),
  printeq(pcd.isprintOPEQ() || pcd.getMode() == ProgramCtxData::EQREWRITING),
  prefix(""),
  collectminimal(pcd.isminDiag() || pcd.isminExp()),
  id1(
			(pcd.getMode() == ProgramCtxData::DIAGREWRITING)?
			pcd.idd1:pcd.ide1),
  id2(
			(pcd.getMode() == ProgramCtxData::DIAGREWRITING)?
			pcd.idd2:pcd.ide2),
  mask1(), mask2(),
  mask(
      (pcd.getMode() == ProgramCtxData::DIAGREWRITING)?
			pcd.brdmask:pcd.bremask),
	nprinter(pcd, id1, id2, mask),
	eqprinter(pcd)
{
  bool anydiag = pcd.isDiag() || pcd.isminDiag();
  bool anyexpl = pcd.isExp() || pcd.isminExp();

  // sanity checks and configure prefix for immediate output
	assert(!!pcd.reg);

	switch(pcd.getMode())
	{
	case ProgramCtxData::DIAGREWRITING:
		// to get diag from expl and vice versa we collect minimal ones
		if( anyexpl )
			collectminimal = true;
		prefix = "D";
		if( printeq )
			prefix += ":EQ";
		break;

	case ProgramCtxData::EXPLREWRITING:
		// to get diag from expl and vice versa we collect minimal ones
		if( printeq )
			throw PluginError("cannot use saturation encoding for calculating equilibria");
		if( anydiag )
			collectminimal = true;
		prefix = "E";
		break;

	case ProgramCtxData::EQREWRITING:
		if( anydiag )
			throw PluginError("cannot use equilibrium encoding for calculating diagnoses");
		if( anyexpl )
			throw PluginError("cannot use equilibrium encoding for calculating explanations");
		prefix = "EQ";
		break;
	}

  // configure partial notion masks
  mask1.setRegistry(pcd.reg);
  mask2.setRegistry(pcd.reg);
  mask1.addPredicate(id1);
  mask2.addPredicate(id2);
}

// if print anything nonminimal (=printanything), do it
// if collect minimal, check against known minimals
//   if subset of existing replace it
//   otherwise if not superset and not equal store new
bool PrintAndAccumulateModelCallback::
operator()(AnswerSetPtr model)
{
  DBGLOG_SCOPE(DBG,"PaAMC",false);
  DBGLOG(DBG,"=PrintAndAccumulateModelCallback::operator()");

  typedef ProgramCtxData::MinimalNotion MinimalNotion;
  typedef ProgramCtxData::MinimalNotionIterator MinimalNotionIterator;

  std::ostream& o = std::cout;

	// printing
	if( printanything )
	{
		o << prefix;
		if( printnotion )
		{
			o << ":";
			nprinter.print(o, model);
		}
		if( printeq )
		{
			o << ":";
			eqprinter.print(o, model);
		}
		o << std::endl;
	}

	// accumulate
  //
  // project to runningmask -> myproj1/myproj2
  // go through all pcd.minimals and compare myprojN with `projected':
  // mark as to-be-added
  // * if projected is the same, add to list `full', mark as do-not-add, and stop processing
  // * if projected is bigger, delete found entry
  // * if projected is smaller, stop processing and mark as do-not-add
  // if to-be-added, add to list

  // project
  InterpretationPtr myproj1(new Interpretation(pcd.reg));
  InterpretationPtr myproj2(new Interpretation(pcd.reg));
  mask1.updateMask();
  mask2.updateMask();
  myproj1->getStorage() =
    model->interpretation->getStorage() & mask1.mask()->getStorage();
  myproj2->getStorage() =
    model->interpretation->getStorage() & mask2.mask()->getStorage();
  bool toBeAdded = true;
  MinimalNotionIterator it = pcd.minimals.begin();
  while(it != pcd.minimals.end())
  {
    DBGLOG(DBG,"checking " << *(it->projected1) << " " << *(it->projected2));
    int res1 = myproj1->getStorage().compare(it->projected1->getStorage());
    int res2 = myproj2->getStorage().compare(it->projected2->getStorage());
    DBGLOG(DBG,"comparison of " << *myproj1 << " with " << *(it->projected1) << " yielded res1=" << res1);
    DBGLOG(DBG,"comparison of " << *myproj2 << " with " << *(it->projected2) << " yielded res2=" << res2);

    if( res1 == 0 && res2 == 0 )
    {
      // equal -> add to list and stop
      it->full.push_back(model);
      toBeAdded = false;
      break;
    }

    int res = res1 + res2;
    if( res < 0 )
    {
      // either one is equal and other smaller
      // therefore the found model is smaller
      // -> delete this entry
      it = pcd.minimals.erase(it);
      continue;
    }

    if( res > 0 )
    {
      // either one is equal and other smaller
      // therefore the found model is bigger
      // -> discard and stop
      toBeAdded = false;
      break;
    }

    ++it;
  }
  if( toBeAdded )
  {
    pcd.minimals.push_back(MinimalNotion(myproj1, myproj2, model));
  }

	// do not abort
	return true;
}


} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=2:sw=2:
