#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#define DEBUG

#include "ACC_ContextAtom.h"

#include <unistd.h>
#include <climits>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>

namespace dlvhex {
  namespace mcsequilibrium {

    void
    ACC_ContextAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
      std::set<std::string> oset,aset,bset;
      std::set<std::string> interset, accset;

      std::string param = query.getInputTuple()[4].getUnquotedString();
      convertQueryToStringSets(query,aset,bset,oset);

      /////////////////////////////////////////////////////////////////
      //
      // get accepted set of beliefsets
      //
      /////////////////////////////////////////////////////////////////
      accset = acc(param,bset);
      std::insert_iterator<std::set<std::string> > out_it(interset, interset.begin());
      set_intersection(accset.begin(), accset.end(), oset.begin(), oset.end(), out_it);

      #ifdef DEBUG 
        std::cout << "are aset and interset equal? \n"; 
        if (aset.size() == interset.size()) {
          if (equal(aset.begin(),aset.end(),interset.begin())) {
            std::cout << "true\n";
          }
          else std::cout << "false\n";  
        }
        else std::cout << "false\n";
      #endif
      if (aset.size() == interset.size()) {
        if (equal(aset.begin(),aset.end(),interset.begin())) {
          Tuple out;
          answer.addTuple(out);
        } 
      }
    } // end ACC_ContextAtom::retrieve()

  } // namespace script
} // namespace dlvhex
