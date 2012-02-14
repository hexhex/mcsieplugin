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
 * @file   MinimalNotionCollector.h
 * @author Peter Schueller
 * 
 * @brief  Utility that collects set of subsetminimal notions (notion = pair of sets).
 */
#ifndef _DLVHEX_MCSDIAGEXPL_MINIMALNOTIONCOLLECTOR_H_
#define _DLVHEX_MCSDIAGEXPL_MINIMALNOTIONCOLLECTOR_H_

#include <dlvhex2/Interpretation.h>
#include <dlvhex2/PredicateMask.h>

#include <boost/shared_ptr.hpp>

#include <list>

namespace dlvhex {
namespace mcsdiagexpl {

class MinimalNotionCollector
{
public:
  // storage for accumulated minimal notions
  struct MinimalNotion
  {
    // notion projected to first/second component
    InterpretationPtr projected1;
    InterpretationPtr projected2;
    // full interpretation (there may be multiple)
    std::list<InterpretationPtr> full;

    MinimalNotion(
        InterpretationPtr proj1, InterpretationPtr proj2, InterpretationPtr firstfull):
      projected1(proj1), projected2(proj2) { full.push_back(firstfull); }
  };

public:
  MinimalNotionCollector(PredicateMask& mask1, PredicateMask& mask2);
  virtual ~MinimalNotionCollector() {}

  virtual void record(InterpretationPtr model);

  const std::list<MinimalNotion>& getMinimals() const
    { return minimals; }

protected:
  // masks to project incoming stuff
	PredicateMask& mask1;
  PredicateMask& mask2;
  std::list<MinimalNotion> minimals;
};
typedef boost::shared_ptr<MinimalNotionCollector>
  MinimalNotionCollectorPtr;

} // END namespace mcsdiagexpl
} // END namespace dlvhex

#endif // _DLVHEX_MCSDIAGEXPL_MINIMALNOTIONCOLLECTOR_H_
