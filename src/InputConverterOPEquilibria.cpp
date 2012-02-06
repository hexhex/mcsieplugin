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
 * @file   InputConverterOPEquilibria.cpp
 * @author Peter Schueller
 * 
 * @brief  Realizes rewriting to obtain output projected equilibria.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "InputConverterOPEquilibria.h"


#include <iostream>
#include <sstream>

namespace dlvhex {
namespace mcsdiagexpl {

namespace
{

void writeBridgeRule(std::ostream& o, const BridgeRule& r);
void writeContext(std::ostream& o, const Context& c);
void writeProgram(std::ostream& o, const MCS& m);

void writeProgram(std::ostream& o, const MCS& m)
{
  for(BridgeRuleIterator it = m.rules.begin();
      it != m.rules.end(); ++it)
  {
    writeBridgeRule(o, *it);
  }
  for(ContextIterator it = m.contexts.begin();
      it != m.contexts.end(); ++it)
  {
    writeContext(o, *it);
  }
}

void writeContext(std::ostream& out, const Context& context)
{
   const int cn = context.ContextNum();

   // guess outputs
   out << "a" << cn << "(X) v na" << cn << "(X) :- o" << cn << "(X)." << std::endl;

   // check context with constraint
   out << ":- not &" << context.ExtAtom()
       << "[" << cn << ",a" << cn << ",b" << cn << ",o" << cn << ","
       << "\"" << context.Param() << "\"]()." << std::endl; 

   // mark context as existing
   out << "ctx(" << cn << ")." << std::endl;
}

void writeBridgeRule(std::ostream& o, const BridgeRule& br)
{
  // write bridgerule in asp form
  std::list<int> ilist;

  // mark outputs: OUT_i via "o<i>(belief)"
  for(BridgeRuleEntryIterator it = br.Body().begin(); it != br.Body().end(); ++it)
  {
    o << asAtom("o", *it) << ".\n";
  }

  // mark input: IN_i via "i<i>(belief)"
  o << asAtom("i", br.Head()) << ".\n";

  // output rule
  o << asAtom("b", br.Head()) << " :- ;

  // output bridge rule body
  for(BridgeRuleEntryIterator it = br.Body().begin();
      it != br.Body().end(); ++it)
  {
    if( it != br.Body().begin() )
      o << ", ";
    const BridgeRuleEntry& elem = *it;
    if( elem.Neg() )
      o << asAtom("na", elem);
    else
      o << asAtom("a", elem);
  }

  o << ".\n";
}

} // anonymous namespace


void InputConverterOPEquilibria::convert(std::istream& i, std::ostream& o)
{
  InputParser p;
  p.parse(i, pcd.mcs());
  
  writeProgram(o, pcd.mcs());
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
