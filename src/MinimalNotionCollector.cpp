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
 * @file   MinimalNotionCollector.cpp
 * @author Peter Schueller
 * 
 * @brief  Utility that collects set of subsetminimal notions (notion = pair of sets).
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MinimalNotionCollector.h"

#include <dlvhex2/Logger.h>

#include <bm/bmalgo_impl.h>

namespace dlvhex {
namespace mcsdiagexpl {

namespace
{

// compare two interpretations subset-wise
// -1 = i1 is subset of i2
// 0 = equal
// 2 = incomparable
// 1 = i2 is subset of i1
int mycompare(InterpretationPtr i1, InterpretationPtr i2)
{
  const unsigned andedcount = bm::count_and(i1->getStorage(), i2->getStorage());
  const unsigned count1 = i1->getStorage().count();
  const unsigned count2 = i2->getStorage().count();
  if( andedcount == count1 && andedcount == count2 )
  {
    return 0;
  }
  if( andedcount == count1 && andedcount < count2 )
  {
    return -1;
  }
  if( andedcount < count1 && andedcount == count2 )
  {
    return 1;
  }
  return 2;
}

} // anonymous namespace

MinimalNotionCollector::MinimalNotionCollector(
    PredicateMask& mask1, PredicateMask& mask2):
  mask1(mask1),
  mask2(mask2)
{
}

void MinimalNotionCollector::record(InterpretationPtr model)
{
  DBGLOG_SCOPE(DBG,"MNCrec",false);

  typedef std::list<MinimalNotion>::iterator MinimalNotionIterator;

  //
  // project to runningmask -> myproj1/myproj2
  // go through all pcd.minimals and compare myprojN with `projected':
  // mark as to-be-added
  // * if projected is the same, add to list `full', mark as do-not-add, and stop processing
  // * if projected is bigger, delete found entry
  // * if projected is smaller, stop processing and mark as do-not-add
  // if to-be-added, add to list

  // project
  RegistryPtr reg = model->getRegistry();
  InterpretationPtr myproj1(new Interpretation(reg));
  InterpretationPtr myproj2(new Interpretation(reg));
  mask1.updateMask();
  mask2.updateMask();
  myproj1->getStorage() =
    model->getStorage() & mask1.mask()->getStorage();
  myproj2->getStorage() =
    model->getStorage() & mask2.mask()->getStorage();
  bool toBeAdded = true;
  MinimalNotionIterator it = minimals.begin();
  DBGLOG(DBG,"processing " << *myproj1 << " " << *myproj2);
  while(it != minimals.end())
  {
    DBGLOG(DBG,"checking " << *(it->projected1) << " " << *(it->projected2));
    int res1 = mycompare(myproj1, it->projected1);
    int res2 = mycompare(myproj2, it->projected2);
    DBGLOG(DBG,"comparison with " << *(it->projected1) << " yielded res1=" << res1);
    DBGLOG(DBG,"comparison with " << *(it->projected2) << " yielded res2=" << res2);

    if( res1 == 0 && res2 == 0 )
    {
      // equal -> add to list and stop
      it->full.push_back(model);
      toBeAdded = false;
      DBGLOG(DBG,"extending list and stopping");
      break;
    }

    if( (res1 == -1 && res2 == 0) || (res1 == 0 && res2 == -1) || (res1 == -1 && res2 == -1) )
    {
      // the found model is smaller than this entry
      // -> delete this entry
      it = minimals.erase(it);
      DBGLOG(DBG,"erasing");
      continue;
    }

    if( (res1 == 1 && res2 == 0) || (res1 == 0 && res2 == 1) || (res1 == 1 && res2 == 1) )
    {
      // the found model is bigger than this entry
      // -> discard and stop
      toBeAdded = false;
      DBGLOG(DBG,"stopping");
      break;
    }

    ++it;
  }
  if( toBeAdded )
  {
    DBGLOG(DBG,"adding");
    minimals.push_back(MinimalNotion(myproj1, myproj2, model));
  }
}

} // END namespace mcsdiagexpl
} // END namespace dlvhex

// vim:ts=2:sw=2:
