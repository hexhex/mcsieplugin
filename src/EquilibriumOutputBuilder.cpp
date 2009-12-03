#include "EquilibriumOutputBuilder.h"
#include "dlvhex/PrintVisitor.h"
#include "dlvhex/globals.h"
#include "dlvhex/ResultContainer.h"

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

  if (((*results.begin())->hasWeights()) && !Globals::Instance()->getOption("AllModels"))
    {
      stream << "Best model: ";
    }
  
  for (ResultContainer::result_t::const_iterator rit = results.begin(); rit != results.end(); ++rit)
    {
      RawPrintVisitor rpv(stream);
      (*rit)->accept(rpv);
      stream << std::endl;

      if ((*rit)->hasWeights())
	{
	  stream << "Cost ([Weight:Level]): <";
	  
	  //
	  // Display all weight values up to the highest specified level
	  //
	  for (unsigned lev = 1; lev <= AnswerSet::getMaxLevel(); ++lev)
	    {
	      if (lev > 1)
		stream << ",";
	      
	      stream << "[" << (*rit)->getWeight(lev) << ":" << lev << "]";
	    }
	  
	  stream << ">" << std::endl;
	}
      
      //
      // empty line
      //
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
