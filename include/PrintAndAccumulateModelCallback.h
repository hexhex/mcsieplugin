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
 * @file   PrintAndAccumulateModelCallback.h
 * @author Peter Schueller
 * 
 * @brief  Model callback for MCSIE (print nonminimal notions, accumulate minimal ones)
 */
#ifndef _DLVHEX_MCSDIAGEXPL_PRINTACCUMULATEMODELCALLBACK_H_
#define _DLVHEX_MCSDIAGEXPL_PRINTACCUMULATEMODELCALLBACK_H_

#include "ProgramCtxData.h"
#include "NotionPrinter.h"
#include "EquilibriumPrinter.h"

#include <dlvhex2/PluginInterface.h>

#include <vector>

namespace dlvhex {
namespace mcsdiagexpl {

class PrintAndAccumulateModelCallback:
  public ModelCallback
{
public:
  PrintAndAccumulateModelCallback(ProgramCtxData& pcd);
	virtual ~PrintAndAccumulateModelCallback() {}

  virtual bool operator()(AnswerSetPtr model);

protected:
  ProgramCtxData& pcd;

  // whether to immediately print encountered models
  bool printanything;
  // whether to print notions (i.e., diagnoses or explanations) in encountered models
  bool printnotion;
  // whether to print equilibria in encountered models
  bool printeq;
  // how encountered models should be prefixed
  std::string prefix;
  // whether to collect subset-minimal parts of models
  bool collectminimal;

	NotionPrinter nprinter;
	EquilibriumPrinter eqprinter;
};

} // END namespace mcsdiagexpl
} // END namespace dlvhex

#endif // _DLVHEX_MCSDIAGEXPL_PRINTACCUMULATEMODELCALLBACK_H_
