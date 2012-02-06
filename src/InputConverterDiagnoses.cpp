/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2009,2010  Markus Boegl
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
 * @file   	InputConverterDiagnoses.cpp
 * @author 	Markus Boegl
 * @author 	Gerald Weidinger
 * @author 	Peter Schueller
 * @date   	Sun Jan 08 13:34:29 2011
 * 
 * @brief  	Converts the Input file when calculating over Diagnosis
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "InputConverterDiagnoses.h"
#include "InputParser.h"
//#include "dlvhex/SpiritDebugging.h"
//#include "BridgeRuleEntry.h"
//#include "Global.h"
//#include "InputConverterDiagnosis.h"


#include <iostream>
#include <sstream>

namespace dlvhex {
namespace mcsdiagexpl {

void InputConverterDiagnoses::convert(std::istream& i, std::ostream& o)
{
  InputParser p;
  p.parse(i, pcd.mcs());
  
  throw std::runtime_error("todo InputConverterDiagnoses?::convert");
}

#if 0

void 
   InputConverterDiagnosis::writeProgram(std::ostream& o, BridgeRule br) {
     // write bridgerule in asp form
     std::list<int> ilist;

     // mark outputs: OUT_i via "o<i>(belief)"
     for (std::vector<BridgeRuleEntry>::iterator it = br.body.begin(); it != br.body.end(); ++it) {
       const BridgeRuleEntry& elem = *it;
       o << "o" << elem << "." << std::endl;
     }

     if ((Global::getInstance())->isKR2010rewriting())
     {
       if ((Global::getInstance())->isSet()) {
       // Only print equilibria
         // output diagnosis disjunction
         o << "normal(" << br.ruleid << ") v d1(" << br.ruleid << ") v d2(" << br.ruleid << ")." << std::endl;
         // output d2 rule
         o << "b" << br.head << " :- d2(" << br.ruleid << ")." << std::endl;
         // output d1 rule
         o << "b" << br.head << " :- not d1(" << br.ruleid << ")";
         if (br.fact)
           o << "." << std::endl;
         else
           o << ", ";
       } else {
         o << "b" << br.head;
         if (br.fact)
           o << "." << std::endl;
         else
           o << " :- ";
       }
     }
     else
     {
       // mark inputs: IN_i via "i<i>(belief)"
       o << "i" << br.head << "." << std::endl;

       // BR evaluation (and diagnosis guessing) (after all contexts ok, indicated by ok(all))
       if ((Global::getInstance())->isSet())
       {
         // diagnosis guessing
         o << "normal(" << br.ruleid << ") v d1(" << br.ruleid << ") v d2(" << br.ruleid << ") :- ok(all)." << std::endl;
         // d2 rule
         o << "c" << br.head << " :- d2(" << br.ruleid << "), ok(all)." << std::endl;
         // d1 rule
         o << "c" << br.head << " :- not d1(" << br.ruleid << "), ok(all)";
         if (br.fact)
           o << "." << std::endl;
         else
           o << ", ";
       }
       else
       {
         // else only print equilibria
         o << "c" << br.head;
         if (br.fact)
           o << "." << std::endl;
         else
           o << " :- ";
       }
     }

     // output bridge rule body
     for (std::vector<BridgeRuleEntry>::iterator it = br.body.begin(); it != br.body.end(); ++it) {
       const BridgeRuleEntry& elem = *it;
       if (elem.Neg())
         o << "n";
       o << "a" << elem;
       if (it+1 != br.body.end())
         o << ", ";
       else
         o << "." << std::endl;
     }
   }


#endif

  } // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
