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

  stream << '(';
  #ifdef DEBUG
    std::cout << "AS size: " << as->size() << std::endl;
  #endif
  if (!as->empty()) {
    for (AtomSet::atomset_t::const_iterator a = as->atoms.begin(); a != as->atoms.end(); ++a) {
      #ifdef DEBUG
        std::cout << std::endl << "Atoms: " << (*a)->getPredicate();
        const Tuple& argu = (*a)->getArguments();
        for (Tuple::const_iterator ait = argu.begin(); ait != argu.end(); ait++) {
          std::stringstream sstr;
          sstr << *ait;
          std::cout << sstr.str() << std::endl;
        } // for over Tuples
      #endif
      std::stringstream sspred;
      sspred << (*a)->getPredicate();
      pred = sspred.str();
      //std::cout << "pred: " << pred << std::endl;
      if (pred[0] != 'a') {
        pred.erase(0,1);
        id = std::atoi(pred.c_str());
        if (id > maxid) maxid=id;
        if (outlist.count(id) < 1) outlist.insert(std::pair<int,std::string>(id,""));
      }
      pred = sspred.str();
      if (pred[0] == 'a') {
        pred.erase(0,1);
        id = std::atoi(pred.c_str());
        if (id > maxid) maxid=id;
        if (outlist.count(id) == 1) {
          if ((outlist.find(id)->second).length() < 1) {
            outlist.erase(outlist.find(id));
          }
        }
        const Tuple& arguments = (*a)->getArguments();
        for (Tuple::const_iterator it = arguments.begin(); it != arguments.end(); it++) {
          std::stringstream sstr;
          sstr << *it;
          //outlist.insert(std::pair<std::string,std::string>(pred,sstr.str()));
          outlist.insert(std::pair<int,std::string>(id,sstr.str()));
        } // for over Tuples
      } // if pred == a<i>
    } // for-loop over AtomSet's

    //std::multimap<std::string,std::string>::iterator oit;
    std::multimap<int,std::string>::iterator oit;
    std::pair<std::multimap<int,std::string>::iterator,std::multimap<int,std::string>::iterator> rangeit;
    //std::string s;
    //int s;

    for (int i=1; i <= maxid; i++) {
      stream << "{";
      rangeit = outlist.equal_range(i);
      for (oit = rangeit.first; oit != rangeit.second; ) {
        stream << oit->second;
        if (++oit != rangeit.second)
           stream << ",";
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
