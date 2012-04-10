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
PrintAndAccumulateModelCallback(
    ProgramCtxData& pcd,
    ID id1, ID id2,
    PredicateMask& fullmask,
    MinimalNotionCollectorPtr mincollector):
  pcd(pcd),
  printanything(false),
  printnotion(pcd.isDiag() || pcd.isExp()),
  printeq(pcd.isprintOPEQ()),
  prefix(""),
  collectminimal(pcd.isminDiag() || pcd.isminExp()),
  id1(id1),
  id2(id2),
  fullmask(fullmask),
  mincollector(mincollector),
	nprinter(pcd, id1, id2, fullmask),
	eqprinter(pcd)
{
  assert((pcd.getMode() != ProgramCtxData::EQREWRITING) &&
      "EQREWRITING shall be printed with PrintEQModelCallback");

  bool anydiag = pcd.isDiag() || pcd.isminDiag();
  bool anyexpl = pcd.isExp() || pcd.isminExp();

  // sanity checks and configure prefix for immediate output
	switch(pcd.getMode())
	{
	case ProgramCtxData::DIAGREWRITING:
		// to get diag from expl and vice versa we collect minimal ones
    printanything = pcd.isDiag();
		if( anyexpl )
			collectminimal = true;
		prefix = "D";
		if( printeq )
			prefix += ":EQ";
		break;

	case ProgramCtxData::EXPLREWRITING:
		// to get diag from expl and vice versa we collect minimal ones
    printanything = pcd.isExp();
		if( printeq )
			throw PluginError("cannot use saturation encoding for calculating equilibria");
		if( anydiag )
			collectminimal = true;
		prefix = "E";
		break;
	}
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

  std::ostream& o = std::cout;

	// printing
	if( printanything )
	{
		o << prefix;
		if( printnotion )
		{
			o << ":";
			nprinter.print(o, model->interpretation);
		}
		if( printeq )
		{
			o << ":";
			eqprinter.print(o, model->interpretation);
		}
		o << std::endl;
	}

	// accumulate
  if( collectminimal )
  {
    assert(!!mincollector);
    mincollector->record(model->interpretation);
  }

	// do not abort
	return true;
}

PrintEQModelCallback::
PrintEQModelCallback(ProgramCtxData& pcd):
  pcd(pcd),
  eqprinter(pcd)
{
  assert((pcd.getMode() == ProgramCtxData::EQREWRITING) &&
      "PrintEQModelCallback can only print EQREWRITING");
  
  bool anydiag = pcd.isDiag() || pcd.isminDiag();
  bool anyexpl = pcd.isExp() || pcd.isminExp();

  if( anydiag )
    throw PluginError("cannot use equilibrium encoding for calculating diagnoses");
  if( anyexpl )
    throw PluginError("cannot use equilibrium encoding for calculating explanations");
}

bool PrintEQModelCallback::
operator()(AnswerSetPtr model)
{
  std::ostream& o = std::cout;

  o << "EQ:";
  eqprinter.print(o, model->interpretation);
  o << std::endl;

  return true;
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=2:sw=2:
