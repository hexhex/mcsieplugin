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
	nprinter(
			pcd,
			(pcd.getMode() == ProgramCtxData::DIAGREWRITING)?
			pcd.idd1:pcd.ide1,
			(pcd.getMode() == ProgramCtxData::DIAGREWRITING)?
			pcd.idd2:pcd.ide2,
			(pcd.getMode() == ProgramCtxData::DIAGREWRITING)?
			pcd.brdmask:pcd.bremask)
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
			prefix += "EQ";
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
}

void PrintAndAccumulateModelCallback::
printEqInModel(std::ostream& o, AnswerSetPtr model)
{
	assert(false && "todo impl");
}

// if print anything nonminimal (=printanything), do it
// if collect minimal, check against known minimals
//   if subset of existing replace it
//   otherwise if not superset and not equal store new
bool PrintAndAccumulateModelCallback::
operator()(AnswerSetPtr model)
{
  std::ostream& o = std::cout;

	// printing
	if( printanything )
	{
		o << prefix;
		if( printnotion )
			nprinter.print(o, model);
		if( printeq )
			printEqInModel(o, model);
		o << std::endl;
	}

	// collecting

	// do not abort
	#warning we could abort if we only print minimal and obtain (0,0)
	return true;
}


} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=2:sw=2:
