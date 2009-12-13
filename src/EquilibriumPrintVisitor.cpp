#include "EquilibriumPrintVisitor.h"
#include "dlvhex/Program.h"
#include "dlvhex/AtomSet.h"
#include "dlvhex/Rule.h"
#include "dlvhex/Literal.h"
#include "dlvhex/Atom.h"
#include "dlvhex/ExternalAtom.h"
#include "dlvhex/AggregateAtom.h"

#include <iostream>
#include <cstdlib>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <boost/functional.hpp>

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
  std::multimap<std::string,std::string> outlist; 
  std::string pred;

  stream << '{';
  if (!as->empty()) {
    for (AtomSet::atomset_t::const_iterator a = as->atoms.begin(); a != --as->atoms.end(); ++a) {
      //(*a)->accept(*this);
      std::stringstream sspred;
      sspred << (*a)->getPredicate();
      pred = sspred.str();
      if (pred[0] == 'a') {
        const Tuple& arguments = (*a)->getArguments();
        for (Tuple::const_iterator it = arguments.begin(); it != arguments.end(); it++) {
          std::stringstream sstr;
          sstr << *it;
          outlist.insert(std::pair<std::string,std::string>(pred,sstr.str()));
        } // for over Tuples
      } // if pred == a<i>
    } // for-loop over AtomSet's

    //(*(--as->atoms.end()))->accept(*this);
    AtomSet::atomset_t::const_iterator at = --as->atoms.end();
    std::stringstream sspred;
    sspred << (*at)->getPredicate();
    pred = sspred.str();
    if (pred[0] == 'a') {
      const Tuple& arguments = (*at)->getArguments();
      for (Tuple::const_iterator it = arguments.begin(); it != arguments.end(); it++) {
        std::stringstream sstr;
        sstr << *it;
        outlist.insert(std::pair<std::string,std::string>(pred,sstr.str()));
      }
    }
    std::multimap<std::string,std::string>::iterator oit;
    std::string s;
    while (!outlist.empty()) {
      oit = outlist.begin();
      s = oit->first;
      stream << "(" << oit->second;
      outlist.erase(oit);
      oit = outlist.find(s);
      while (oit != outlist.end()) {
        stream << "," << oit->second;
        outlist.erase(oit);
        oit = outlist.find(s);
      }
      stream << ")";
      if (!outlist.empty()) stream << ",";
    }
  } // if empty
  stream << '}';
}//EquilibriumPrintVisitor::visit(AtomSet* const as)

}//namespace mcsequilibrium
}//namespace dlvhex

/* vim: set noet sw=4 ts=4 tw=80: */


// Local Variables:
// mode: C++
// End:
