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
 * @file   ACC_ContextAtom.cpp
 * @author Markus Boegl
 * @date   Sun Jan 24 13:24:22 2010
 * 
 * @brief  Base Class for User implemented Context Atoms
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "ACC_ContextAtom.h"
//#include "Timing.h"

#include <dlvhex2/Logger.h>
#include <dlvhex2/Benchmarking.h>
#include <dlvhex2/Registry.h>

#include <ostream>

namespace dlvhex {
namespace mcsdiagexpl {

void
ACC_ContextAtom::retrieve(const Query& query, Answer& answer)
{
  DBGLOG_SCOPE(DBG,"ACA::r",false);
  DBGLOG(DBG,"ACC_ContextAtom::retrieve");

  // query.input is tuple [context_id,belief_pred,input_pred,outputs_pred,program]

  bool accept = false;

  /////////////////////////////////////////////////////////////////
  //
  // get the parameter out of the External Atom
  // get the belief set's out of the External Atom an fill in the
  // stringset's
  //
  /////////////////////////////////////////////////////////////////
  const std::string& param = registry->terms.getByID(query.input[4]).symbol;
  // aset = belief_pred, bset = inputs_pred, oset = outputs_pred
  StringSet aset, bset, oset;
  convertQueryToStringSets(query,aset,bset,oset);

  /////////////////////////////////////////////////////////////////
  //
  // get accepted set of beliefsets
  //
  /////////////////////////////////////////////////////////////////

  //if((Timing::getInstance())->isActive()) {
  //  (Timing::getInstance())->start(context_id);
  //}
  std::set<std::set<std::string> > accset;
  {
    DLVHEX_BENCHMARK_REGISTER_AND_SCOPE(sid,"ACC_ContextAtom call acc()");
    accset = acc(param,bset);
  }
  //if((Timing::getInstance())->isActive()) {
  //  (Timing::getInstance())->stop(context_id);
  //}

  /////////////////////////////////////////////////////////////////
  //
  // Iterate throw the accepted set's, 
  // build intersection with Output-beliefs
  // and compare to beliefs in Bridgerulebody
  // if there's at least one set equal, the answerset is accepted.
  //
  /////////////////////////////////////////////////////////////////
  for (std::set<StringSet>::iterator setit = accset.begin(); 
            ((setit != accset.end()) && (!accept)); ++setit) {
    StringSet interset;
    std::insert_iterator<StringSet> out_it(interset, interset.begin());
    set_intersection((*setit).begin(), (*setit).end(), oset.begin(), oset.end(), out_it);
    if (aset.size() == interset.size()) {
      if (equal(aset.begin(),aset.end(),interset.begin())) {
        // accept -> add tuple
        answer.get().push_back(Tuple());
        // can exit now
        return;
      } 
    }
  }

  // did not accept -> mark as used nevertheless
  answer.use();
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
