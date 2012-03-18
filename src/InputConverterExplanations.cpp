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
 * @file   InputConverterExplanations.cpp
 * @author Gerald Weidinger
 * @author Peter Schueller (refactored)
 * @date   Sun Jan 24 13:34:29 2010
 * 
 * @brief  Realizes rewriting to obtain explanations (via saturation).
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "InputConverterExplanations.h"
#include "InputParser.h"
#include "MCS.h"

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

void writeContext(std::ostream& o, const Context& context)
{
   const int cn = context.ContextNum();

   // guess oputs
   o << "a" << cn << "(X) v na" << cn << "(X) :- o" << cn << "(X).\n";

   // saturate on spoil
   o << "a" << cn << "(X) :- o" << cn << "(X), spoil.\n";
   o << "na" << cn << "(X) :- o" << cn << "(X), spoil.\n";

   // spoil if guesses are contradictory
   o << "spoil :- a" << cn << "(X), na" << cn << "(X).\n";

   // check context with constraint
   o << ":- not &" << context.ExtAtom()
       << "[" << cn << ",a" << cn << ",b" << cn << ",o" << cn << ","
       << "\"" << context.Param() << "\"]().\n"; 

    // spoil if the guessed belief state is no equilibrium
    o <<
      "spoil :- not &saturation_meta_context[\"" << context.ExtAtom()  <<"\",spoil," <<
      cn << ",a" << cn << ",b" << cn << ",o" << cn << "," <<
      "\"" << context.Param() << "\"].\n"; 

   // mark context as existing
   o << "ctx(" << cn << ")." << std::endl;
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

  // guess explanation candidate (independently for e1 and e2)
  o << "e1(" << br.Id() << ") v ne1(" << br.Id() << ").\n";
  o << "e2(" << br.Id() << ") v ne2(" << br.Id() << ").\n";

  // guess set of rules (r1,r2) such that
  //
  // e1 \subseteq r1 \subseteq BR
  o << "r1(" << br.Id() << ") :- e1(" << br.Id() << ").\n";
  o << "r1(" << br.Id() << ") v nr1(" << br.Id() << ") :- ne1(" << br.Id() << ").\n";
  // r2 \subseteq BR \setminus e2
  o << "r2(" << br.Id() << ") v nr2(" << br.Id() << ") :- ne2(" << br.Id() << ").\n";

  // spoil if guess is contradictory
  o << "spoil :- r1(" << br.Id() << "), nr1(" << br.Id() << ").\n";
  o << "spoil :- r2(" << br.Id() << "), nr2(" << br.Id() << ").\n";

  // output r1 rule
  o << asAtom("b", br.Head()) << " :- r1(" << br.Id() << ")";
  for(BridgeRuleEntryIterator it = br.Body().begin();
      it != br.Body().end(); ++it)
  {
    const BridgeRuleEntry& elem = *it;
    if( elem.Neg() )
      o << ", " << asAtom("na", elem);
    else
      o << ", " << asAtom("a", elem);
  }
  o << ".\n";

  // output r2 rule
  o << asAtom("b", br.Head()) << " :- r2(" << br.Id() << ").\n";

  // saturate on spoil
  o << "r1("  << br.Id() << ") :- spoil.\n";
  o << "nr1(" << br.Id() << ") :- spoil.\n";
  o << "r2("  << br.Id() << ") :- spoil.\n";
  o << "nr2(" << br.Id() << ") :- spoil.\n";
  o << asAtom("b", br.Head()) << " :- spoil.\n";
}

} // anonymous namespace

void InputConverterExplanations::convert(std::istream& i, std::ostream& o)
{
  InputParser p;
  p.parse(i, pcd.mcs());
  
  writeProgram(o, pcd.mcs());
}

} // namespace mcsdiagexpl
} // namespace dlvhex

// vim:ts=8:
