#include "EquilibriumOutputBuilder.h"
#include "dlvhex/globals.h"
#include "dlvhex/ResultContainer.h"
#include "EquilibriumPrintVisitor.h"

#include <iostream>

namespace dlvhex {
  namespace mcsequilibrium {

EquilibriumOutputBuilder::EquilibriumOutputBuilder()
{ }


EquilibriumOutputBuilder::~EquilibriumOutputBuilder()
{ }


void
EquilibriumOutputBuilder::buildResult(std::ostream& stream, const ResultContainer& facts)
{
  const ResultContainer::result_t& results = facts.getAnswerSets();

  if (!Globals::Instance()->getOption("Silent"))
    {
      stream << std::endl;
    }

  if (results.empty())
    {
      return;
    }
  
  for (ResultContainer::result_t::const_iterator rit = results.begin(); rit != results.end(); ++rit)
    {
  #if 0
      RawPrintVisitor rpv(stream);
      (*rit)->accept(rpv);
      stream << std::endl;
  #endif

      EquilibriumPrintVisitor epv(stream);
      (*rit)->accept(epv);
      stream << std::endl;

      if (!Globals::Instance()->getOption("Silent"))
	{
	  stream << std::endl;
	}
    }
}

}//namespace mcsequilibrium
}//namespace dlvhex

/* vim: set noet sw=4 ts=4 tw=80: */


// Local Variables:
// mode: C++
// End:
