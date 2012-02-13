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
 * @file   MinPrintDualConvertFinalCallback.cpp
 * @author Peter Schueller
 * 
 * @brief  Final callback for MCSIE (prints minimal notions, converts to dual notion)
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MinPrintDualConvertFinalCallback.h"

#include <cassert>

namespace dlvhex {
namespace mcsdiagexpl {

MinPrintDualConvertFinalCallback::
MinPrintDualConvertFinalCallback(ProgramCtxData& pcd, PrintAndAccumulateModelCallback& mcb):
	pcd(pcd),
  mcb(mcb),
  nprinter(mcb.nprinter),
  eqprinter(mcb.eqprinter)
{
}

DiagRewritingFinalCallback::
DiagRewritingFinalCallback(ProgramCtxData& pcd, PrintAndAccumulateModelCallback& mcb):
  MinPrintDualConvertFinalCallback(pcd,mcb)
{
}

ExplRewritingFinalCallback::
ExplRewritingFinalCallback(ProgramCtxData& pcd, PrintAndAccumulateModelCallback& mcb):
  MinPrintDualConvertFinalCallback(pcd,mcb)
{
}

void DiagRewritingFinalCallback::
operator()()
{
  typedef ProgramCtxData::MinimalNotion MinimalNotion;
  typedef ProgramCtxData::MinimalNotionIterator MinimalNotionIterator;

  std::ostream& o = std::cout;

	if( pcd.isminDiag() )
  {
    // print minimal diagnosis notions
    for(MinimalNotionIterator it = pcd.minimals.begin();
        it != pcd.minimals.end(); ++it)
    {
      if( pcd.isprintOPEQ() )
      {
        for(std::list<AnswerSetPtr>::const_iterator itl = it->full.begin();
            itl != it->full.end(); ++itl)
        {
          o << "Dm:EQ:";
          nprinter.print(o, *itl);
          o << ":";
          eqprinter.print(o,*itl);
          o << std::endl;
        }
      }
      else
      {
        o << "Dm:";
        nprinter.print(o, it->full.front());
        o << std::endl;
      }
    }
  }

	if( pcd.isminExp() || pcd.isExp() )
		assert(false && "convertion to explanation not implemented");

}

void ExplRewritingFinalCallback::
operator()()
{
  std::ostream& o = std::cout;

  assert(false && "not implemented");
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=2:sw=2:
