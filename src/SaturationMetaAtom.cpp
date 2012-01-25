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
//#include "Timing.h"
//#include "Global.h"

#include <dlvhex2/PluginInterface.h>

#include <boost/algorithm/string.hpp>


namespace dlvhex {
  namespace mcsdiagexpl {
      

      void SaturationMetaAtom::retrieve(const Query& query, Answer& answer) {
	  // check if saturation is the case
        throw std::runtime_error("todo implement SaturationMetaAtom::retrieve");
        #if 0
	  const std::string& sat_pred = query.getInputTuple()[1].getUnquotedString();
	  AtomSet interpretation = query.getInterpretation();
	  AtomSet saturation;
	  interpretation.matchPredicate(sat_pred,saturation);
	  
	  if( saturation.empty() ) {
	      // saturation is not the case, check if context is consistent

	      // find the external atom of the context
            // TODO the contextname is the name of the context processing atom?
	      std::string contextname = query.getInputTuple()[0].getUnquotedString();
	      boost::shared_ptr<PluginAtom> pa=Global::getInstance()->
		  getProgramCtx()->getPluginContainer()->getAtom(contextname);
	      
	      // construct query to context atom
	      AtomSet interp;
	      interp.insert(interpretation);
	      interp.remove(sat_pred); // remove saturation predicate
	      Tuple input=query.getInputTuple();
	      input.erase(input.begin(),input.begin()+2); // remove first two inputs
	      Tuple pat=query.getPatternTuple();
	      Query *qcon = new Query(interp,input,pat);
	      
	      // call external context atom
	      pa->retrieve(*qcon,answer);
	  }
	  else {
	      // saturation is the case, signal that context is inconsistent
	      // by adding no tuple to &answer
	  }
          #endif
      }
      


  } // namespace mcsequilibrium
} // namespace dlvhex
// vim:ts=8:
