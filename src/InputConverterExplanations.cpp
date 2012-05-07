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

typedef std::list<BridgeRule> BridgeRuleList;
typedef BridgeRuleList::const_iterator BridgeRuleListIterator;

typedef std::map<BridgeRuleEntry, BridgeRuleList > BridgeRulesByHead;
typedef BridgeRulesByHead::iterator BridgeRulesByHeadIterator;

void writeBridgeRulesForOneHead(
    std::ostream& o,
    const BridgeRuleEntry& head, const BridgeRuleList& r,
    unsigned& atbody_base);
void writeContext(std::ostream& o, const Context& c);
void writeProgram(std::ostream& o, const MCS& m);

void writeProgram(std::ostream& o, const MCS& m)
{
  BridgeRulesByHead br_by_head;

  for(BridgeRuleIterator it = m.rules.begin();
      it != m.rules.end(); ++it)
  {
    BridgeRulesByHeadIterator byit = br_by_head.find(it->Head());
    if( byit == br_by_head.end() )
    {
      BridgeRuleList brl;
      brl.push_back(*it);
      br_by_head.insert(std::make_pair(it->Head(), brl));
    }
    else
    {
      BridgeRuleList& brl = byit->second;
      brl.push_back(*it);
    }
  }

  unsigned atbody = 1;
  for(BridgeRulesByHeadIterator byit = br_by_head.begin();
      byit != br_by_head.end(); ++byit)
  {
    writeBridgeRulesForOneHead(o, byit->first, byit->second, atbody);
  }

  for(ContextIterator it = m.contexts.begin();
      it != m.contexts.end(); ++it)
  {
    writeContext(o, *it);
  }

  o << ":- not spoil." << std::endl;
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

   // spoil if the guessed belief state is no equilibrium
   o <<
      "spoil :- &saturation_meta_context[\"" << context.ExtAtom()  <<"\",spoil," <<
      cn << ",a" << cn << ",b" << cn << ",o" << cn << "," <<
      "\"" << context.Param() << "\"].\n"; 

   // mark context as existing
   o << "ctx(" << cn << ")." << std::endl;
}

#if 0
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
#endif

void writeBridgeRulesForOneHead(
    std::ostream& o,
    const BridgeRuleEntry& head, const BridgeRuleList& r,
    unsigned& atbody_base)
{
  // for all bridge rules in this list
  for(BridgeRuleListIterator itr = r.begin(); 
      itr != r.end(); ++itr)
  {
    // mark outputs: OUT_i via "o<i>(belief)"
    for(BridgeRuleEntryIterator it = itr->Body().begin(); it != itr->Body().end(); ++it)
    {
      o << asAtom("o", *it) << ".\n";
    }

    // mark input: IN_i via "i<i>(belief)"
    o << asAtom("i", head) << ".\n";

    // guess explanation candidate (independently for e1 and e2)
    o << "e1(" << itr->Id() << ") v ne1(" << itr->Id() << ").\n";
    o << "e2(" << itr->Id() << ") v ne2(" << itr->Id() << ").\n";

    // guess set of rules (r1,r2) such that
    //
    // e1 \subseteq r1 \subseteq BR
    o << "r1(" << itr->Id() << ") :- e1(" << itr->Id() << ").\n";
    o << "r1(" << itr->Id() << ") v nr1(" << itr->Id() << ") :- ne1(" << itr->Id() << ").\n";
    // r2 \subseteq BR \setminus e2
    o << "r2(" << itr->Id() << ") v nr2(" << itr->Id() << ") :- ne2(" << itr->Id() << ").\n";
    o << "nr2(" << itr->Id() << ") :- e2(" << itr->Id() << ").\n";

    // spoil if guess is contradictory
    o << "spoil :- r1(" << itr->Id() << "), nr1(" << itr->Id() << ").\n";
    o << "spoil :- r2(" << itr->Id() << "), nr2(" << itr->Id() << ").\n";
  }

  // for all bridge rules in this list

  // output rules for body 1 -> bdy_1 -> head, body 2 -> bdy_2 -> head, ..., r2 -> head
  unsigned atbody = atbody_base;
  for(BridgeRuleListIterator itr = r.begin(); 
      itr != r.end(); ++itr, ++atbody)
  {
    const BridgeRule& br = *itr;

    // bdy_integer :- r1 + body
    o << "bdy" << atbody << " :- " << "r1(" << br.Id() << ")";
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

    // head :- bdy_integer
    o << asAtom("b", head) << " :- bdy" << atbody << ".\n";

    // head :- r2 rule
    o << asAtom("b", head) << " :- r2(" << br.Id() << ").\n";
  }

  // output rule for head -> one of bodies
  atbody = atbody_base;
  for(BridgeRuleListIterator itr = r.begin(); 
      itr != r.end(); ++itr, ++atbody)
  {
    if( atbody != atbody_base )
      o << " v ";
    // r2 rule v bdy
    o << "r2(" << itr->Id() << ") v " << "bdy" << atbody;
  }
  o << " :- " << asAtom("b", head) << ".\n";

  // output rules for bdy_integer -> body atoms
  atbody = atbody_base;
  for(BridgeRuleListIterator itr = r.begin(); 
      itr != r.end(); ++itr, ++atbody)
  {
    for(BridgeRuleEntryIterator it = itr->Body().begin();
        it != itr->Body().end(); ++it)
    {
      const BridgeRuleEntry& elem = *it;
      if( elem.Neg() )
        o << asAtom("na", elem);
      else
        o << asAtom("a", elem);
      o << " :- " << "bdy" << atbody << ".\n";
    }
  }

  // saturate on spoil
  atbody = atbody_base;
  for(BridgeRuleListIterator itr = r.begin(); 
      itr != r.end(); ++itr, ++atbody)
  {
    const BridgeRule& br = *itr;
    o << "bdy" << atbody << " :- spoil.\n";
    o << "r1("  << br.Id() << ") :- spoil.\n";
    o << "nr1(" << br.Id() << ") :- spoil.\n";
    o << "r2("  << br.Id() << ") :- spoil.\n";
    o << "nr2(" << br.Id() << ") :- spoil.\n";
  }
  o << asAtom("b", head) << " :- spoil.\n";

  atbody_base = atbody;
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
