#include "EquilibriumPrintVisitor.h"
#include "dlvhex/Program.h"
#include "dlvhex/AtomSet.h"
#include "dlvhex/Rule.h"
#include "dlvhex/Literal.h"
#include "dlvhex/Atom.h"
#include "dlvhex/ExternalAtom.h"
#include "dlvhex/AggregateAtom.h"
#include "dlvhex/PrintVisitor.h"

#include <iostream>
#include <cstdlib>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <boost/functional.hpp>

//#define DEBUG

namespace dlvhex {
  namespace mcsequilibrium {
////////////////////////////////////////////////////////////////////////////
// 
//	PrintVisitorMethods
//
////////////////////////////////////////////////////////////////////////////
EquilibriumPrintVisitor::EquilibriumPrintVisitor(std::ostream& s)
: RawPrintVisitor(s)
{ }

void
EquilibriumPrintVisitor::visit(AtomSet* const as)
{
  std::multimap<int,std::string> outlist; 
  std::string pred;
  int id=0,maxid=0;

  #ifdef DEBUG
    std::cerr << "Answerset: ";
		::dlvhex::RawPrintVisitor dbgVisitor(std::cerr);
		as->accept(dbgVisitor);
		std::cerr << std::endl;
  #endif

  stream << '(';
  if (!as->empty()) {
    for (AtomSet::atomset_t::const_iterator a = as->atoms.begin(); a != as->atoms.end(); ++a) {
	// get predicate (we are interested in o<i> a<i> d1 d2)
	std::string pred;
	{
		std::stringstream s; s << (*a)->getPredicate();
		pred = s.str();
	}
	assert(!pred.empty());

	// get argument
	std::string arg;
	{
        	const Tuple& arguments = (*a)->getArguments();
		assert(arguments.size() == 1);
		std::stringstream s; s << arguments[0];
		arg = s.str();
	}

	// process pred
	if( pred[0] == 'o' or pred[0] == 'a' or pred[0] == 'b' ) {
		std::stringstream s; s << pred.substr(1,std::string::npos);
		s >> id;
		// remember max index for contexts
		if (id > maxid) maxid=id;

		// if "a<i>", add belief to output container
		if( pred[0] == 'a' )
			outlist.insert(std::make_pair(id,arg));
		}
    } // for-loop over AtomSet's

    std::multimap<int,std::string>::iterator oit;
    std::pair<std::multimap<int,std::string>::iterator,std::multimap<int,std::string>::iterator> rangeit;

    for (int i=1; i <= maxid; i++) {
	stream << "{";
	if( outlist.count(i) > 0 ) {
		rangeit = outlist.equal_range(i);
		for (oit = rangeit.first; oit != rangeit.second; ) {
			stream << oit->second;
			if (++oit != rangeit.second)
			  stream << ",";
		}
	}
	stream << "}";
	if (i < maxid) stream << ",";
    }//end for-loop over int
  } // if empty
  stream << ')';
}//EquilibriumPrintVisitor::visit(AtomSet* const as)

}//namespace mcsequilibrium
}//namespace dlvhex

/* vim: set noet sw=4 ts=4 tw=80: */


// Local Variables:
// mode: C++
// End:
