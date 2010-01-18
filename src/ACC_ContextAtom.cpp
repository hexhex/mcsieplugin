#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "ACC_ContextAtom.h"
//#include <unistd.h>
//#include <climits>
//#include <cstring>
//#include <sstream>
//#include <cstdlib>
//#include <iostream>
//#include <algorithm>

namespace dlvhex {
  namespace mcsequilibrium {

    void
    ACC_ContextAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
      bool accept = false;
      std::set<std::string> oset,aset,bset,interset;
      std::set<std::set<std::string> > accset;

      /////////////////////////////////////////////////////////////////
      //
      // get the parameter out of the External Atom
      // get the belief set's out of the External Atom an fill in the
      // stringset's
      //
      /////////////////////////////////////////////////////////////////
      std::string param = query.getInputTuple()[4].getUnquotedString();
      convertQueryToStringSets(query,aset,bset,oset);

      /////////////////////////////////////////////////////////////////
      //
      // get accepted set of beliefsets
      //
      /////////////////////////////////////////////////////////////////

      accset = acc(param,bset);

      /////////////////////////////////////////////////////////////////
      //
      // Iterate throw the accepted set's, 
      // build intersection with Output-beliefs
      // and compare to beliefs in Bridgerulebody
      // if there's at least one set equal, the answerset is accepted.
      //
      /////////////////////////////////////////////////////////////////
      for (std::set<std::set<std::string> >::iterator setit = accset.begin(); ((setit != accset.end()) && (!accept)); ++setit) {
	interset.clear();
	std::insert_iterator<std::set<std::string> > out_it(interset, interset.begin());
        set_intersection((*setit).begin(), (*setit).end(), oset.begin(), oset.end(), out_it);
        if (aset.size() == interset.size()) {
          if (equal(aset.begin(),aset.end(),interset.begin())) {
            accept = true;
          } 
        }
      }

      if (accept) {
        Tuple out;
	answer.addTuple(out);
      }
    } // end ACC_ContextAtom::retrieve()

  } // namespace mcsequilibrium
} // namespace dlvhex
