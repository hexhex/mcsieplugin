/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2009,2010  Markus Boegl
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
 * @file   EquilibriumOutputBuilder.cpp
 * @author Markus Boegl
 * @date   Sun Jan 24 13:40:01 2010
 * 
 * @brief  OutputBuilder to write the Answersets as Equilibria
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "EquilibriumOutputBuilder.h"
#include "dlvhex/globals.h"
#include "dlvhex/ResultContainer.h"
#include "EquilibriumPrintVisitor.h"
#include "Timing.h"

#include <iostream>

namespace dlvhex {
  namespace mcsdiagexpl {

EquilibriumOutputBuilder::EquilibriumOutputBuilder()
{ }


EquilibriumOutputBuilder::~EquilibriumOutputBuilder()
{ }


void
EquilibriumOutputBuilder::buildResult(std::ostream& stream, const ResultContainer& facts)
{
  if((Timing::getInstance())->isActive()) {
	(Timing::getInstance())->end();
  }
  const ResultContainer::result_t& results = facts.getAnswerSets();

  if (!Globals::Instance()->getOption("Silent"))
    {
      stream << std::endl;
    }

  if (!results.empty()) {
	for (ResultContainer::result_t::const_iterator rit = results.begin(); rit != results.end(); ++rit) {
	      EquilibriumPrintVisitor epv(stream);
	      (*rit)->accept(epv);
	      stream << std::endl;

	      if (!Globals::Instance()->getOption("Silent"))
		{
		  stream << std::endl;
		}
	    }
  }

  if((Timing::getInstance())->isActive()) {
	stream << std::endl;
	stream << *Timing::getInstance();
  }

  if (results.empty())
    {
      return;
    }

}

}//namespace mcsdiagexpl
}//namespace dlvhex
