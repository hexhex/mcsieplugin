#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "GenericContextAtom.h"

#include <unistd.h>
#include <climits>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <iostream>

namespace dlvhex {
  namespace mcsequilibrium {

    class DLV_ASP_Context : public GenericContextAtom {

      public:
        DLV_ASP_Context(std::string hex_atom) : GenericContextAtom(hex_atom) {}

	/*set<set<string> > acc(const string& param, const set<string>& input) {
		set<set<string> > ret;
		return ret;
	} // end ACC implementation*/
    };

  } // namespace script
} // namespace dlvhex
