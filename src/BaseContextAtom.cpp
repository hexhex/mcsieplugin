/**
 * @file   BaseContextAtom.cpp
 * @author Peter Schueller
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "BaseContextAtom.h"

#include <dlvhex2/Logger.h>
#include <dlvhex2/Registry.h>
#include <dlvhex2/Interpretation.h>

namespace dlvhex {
namespace mcsdiagexpl {

void BaseContextAtom::convertQueryToStringSets(
    const Query& query,
    StringSet& aset, StringSet& bset, StringSet& oset)
{
  ID apredid = query.input[1];
  ID inputsPredID = query.input[2];
  ID opredid = query.input[3];

  const Interpretation::Storage& storage = query.interpretation->getStorage();
  Interpretation::Storage::enumerator it;
  ID oaid(ID::MAINKIND_ATOM | ID::SUBKIND_ATOM_ORDINARYG, 0);
  for(it = storage.first(); it != storage.end(); ++it)
  {
    // create ID
    oaid.address = *it;
    // lookup
    const OrdinaryAtom& oa = registry->ogatoms.getByID(oaid);
    assert(oa.tuple.size() == 2);
    DBGLOG(DBG,"got term " << oa.tuple[1]);
    const Term& term = registry->terms.getByID(oa.tuple[1]);
    DBGLOG(DBG,"this is symbol " << term.symbol);

    if( oa.tuple[0] == apredid )
    {
      aset.insert(term.symbol);
    }
    else if( oa.tuple[0] == opredid )
    {
      oset.insert(term.symbol);
    }
    else if( oa.tuple[0] == inputsPredID )
    {
      bset.insert(term.symbol);
    }
  }
  DBGLOG(DBG,"got output beliefs: " << printrange(oset));
  DBGLOG(DBG,"got present output beliefs: " << printrange(aset));
  DBGLOG(DBG,"got bridge rule inputs: " << printrange(bset));
}

} // namespace mcsequilibrium
} // namespace dlvhex

// vim:ts=8:
