/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2012 Peter Schueller
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
 * @file   MinPrintDualConvertFinalCallback.h
 * @author Peter Schueller
 * 
 * @brief  Final callback for MCSIE (prints minimal notions, converts to dual notion)
 */
#ifndef _DLVHEX_MCSDIAGEXPL_FINALCALLBACK_H_
#define _DLVHEX_MCSDIAGEXPL_FINALCALLBACK_H_

#include "ProgramCtxData.h"
#include "PrintAndAccumulateModelCallback.h"

#include <dlvhex2/PluginInterface.h>
#include <dlvhex2/ASPSolverManager.h>

#include <vector>

namespace dlvhex {
namespace mcsdiagexpl {

class MinPrintDualConvertFinalCallback:
	public FinalCallback
{
public:
	MinPrintDualConvertFinalCallback(ProgramCtxData& pcd, PrintAndAccumulateModelCallback& mcb, ASPSolverManager::SoftwareConfigurationPtr software);
	virtual ~MinPrintDualConvertFinalCallback() {}

protected:
	ProgramCtxData& pcd;
  PrintAndAccumulateModelCallback& mcb;
  ASPSolverManager::SoftwareConfigurationPtr software;

  // from within mcb
  NotionPrinter& nprinter;
  EquilibriumPrinter& eqprinter;
};

class DiagRewritingFinalCallback:
  public MinPrintDualConvertFinalCallback
{
public:
	DiagRewritingFinalCallback(ProgramCtxData& pcd, PrintAndAccumulateModelCallback& mcb, ASPSolverManager::SoftwareConfigurationPtr software);
	virtual ~DiagRewritingFinalCallback() {}

  virtual void operator()();
};

class ExplRewritingFinalCallback:
  public MinPrintDualConvertFinalCallback
{
public:
	ExplRewritingFinalCallback(ProgramCtxData& pcd, PrintAndAccumulateModelCallback& mcb, ASPSolverManager::SoftwareConfigurationPtr software);
	virtual ~ExplRewritingFinalCallback() {}

  virtual void operator()();
};

} // END namespace mcsdiagexpl
} // END namespace dlvhex

#endif // _DLVHEX_MCSDIAGEXPL_FINALCALLBACK_H_
