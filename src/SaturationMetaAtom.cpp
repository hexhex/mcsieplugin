/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2010  Antonius Weinzierl
 * Copyright (C) 2012  Peter Schueller
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
 * @file   SaturationMetaAtom.cpp
 * @author Antonius Weinzierl
 * @author Peter Schueller
 * 
 * @brief  Meta atom for saturation encoding, can query other external atoms
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "SaturationMetaAtom.h"
#include "BaseContextAtom.h"

#include <dlvhex2/Registry.h>

//#include "Global.h"

//#include <boost/algorithm/string.hpp>


namespace dlvhex {
namespace mcsdiagexpl {

SaturationMetaAtom::SaturationMetaAtom(ProgramCtxData& pcd):
  PluginAtom("saturation_meta_context", false),
  pcd(pcd)
{
  // context atom name
  addInputConstant();
  // saturation/spoil predicate
  addInputPredicate();
  // context id
  addInputConstant();
  // active output belief predicate
  addInputPredicate();
  // active input belief predicate
  addInputPredicate();
  // output belief interface predicate
  addInputPredicate();
  // context evaluation parameter to be passed onto context atom
  addInputConstant();
  setOutputArity(0);
}

void SaturationMetaAtom::retrieve(const Query& query, Answer& answer)
{
  LOG_SCOPE(INFO,"SMA",false);
  LOG(INFO,"= SaturationMetaAtom::retrieve");

  assert(query.input.size() == 7);

  // id of constant of saturate/spoil predicate
  ID saturate_pred = query.input[1];

  // get id of 0-ary atom
  OrdinaryAtom saturate_oatom(ID::MAINKIND_ATOM | ID::SUBKIND_ATOM_ORDINARYG);
  saturate_oatom.tuple.push_back(saturate_pred);
  ID saturate_atom = registry->storeOrdinaryGAtom(saturate_oatom);
  DBGLOG(DBG,"got saturate_pred=" << saturate_pred << " and saturate_atom=" << saturate_atom);

  // check if atom <saturate_pred> is true in interpretation
  bool saturate = query.interpretation->getFact(saturate_atom.address);
  LOG(DBG,"SaturationMetaAtom called with saturate=" << saturate);

  if( saturate )
  {
    // saturation is the case, signal that context is inconsistent
    // by adding no tuple to answer
    LOG(INFO,"saturate is true -> returning no tuples");
    answer.use(); // mark as used, this is required if we do not add tuples
  }
  else
  {
    // saturation is not the case, check if context is consistent

    // name of context external atom
    ID contextatomname_id = query.input[0];
    const std::string& contextatomname_str = registry->getTermStringByID(contextatomname_id);
    assert(contextatomname_str.size() > 2);
    const std::string contextatomname(contextatomname_str,1,contextatomname_str.size()-2);
    DBGLOG(DBG,"got context atom id " << contextatomname_id << " and name '" << contextatomname << "'");

    ContextAtomPtr cat = pcd.getContextAtom(contextatomname);
    assert(!!cat);

    // construct query to context atom
    InterpretationPtr queryint;
    {
      // build interpretation without saturation atom
      // TODO this should not be necessary!
      queryint.reset(new Interpretation(registry));
      queryint->add(*query.interpretation);
      queryint->clearFact(saturate_atom.address);
    }
    Query childQuery(
        queryint,
        // remove first two inputs
        Tuple(query.input.begin()+2,query.input.end()),
        query.pattern);

    // call external context atom
    LOG(INFO,"saturate is false -> delegating to context atom " << contextatomname);
    cat->retrieve(childQuery, answer);
  }
}



} // namespace mcsequilibrium
} // namespace dlvhex
// vim:ts=8:
