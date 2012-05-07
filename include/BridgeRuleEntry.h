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
 * @file   BridgeRuleEntry.h
 * @author Markus Boegl
 * @author Peter Schueller
 * @date   Sun Jan 24 13:30:59 2010
 * 
 * @brief  Bridge rule head or body literal representation
 */
#ifndef _DLVHEX_MCSDIAGEXPL_BRIDGERULEENTRY_H_
#define _DLVHEX_MCSDIAGEXPL_BRIDGERULEENTRY_H_

#include <dlvhex2/Printhelpers.h>

#include <string>

namespace dlvhex {
namespace mcsdiagexpl {

class BridgeRuleEntry:
  public ostream_printable<BridgeRuleEntry>
{
private:
  int contextid;
  std::string fact;
  bool neg;

public:
  BridgeRuleEntry(int id, std::string f, bool n=false);
  BridgeRuleEntry();

  int ContextID() const { return contextid; }
  std::string Fact() const { return fact; }
  bool Neg() const { return neg; }

  std::ostream& print(std::ostream&) const;

  bool operator<(const BridgeRuleEntry& other) const
  {
    return
      (contextid < other.contextid) ||
      (contextid == other.contextid && fact < other.fact) ||
      (contextid == other.contextid && fact == other.fact && neg < other.neg);
  }
};

std::ostream& printBridgeRuleEntryAsASPHelperAtom(std::ostream& o, const char* prefix, const BridgeRuleEntry& entry);

inline print_container* asAtom(const char* prefix, const BridgeRuleEntry& entry)
{
  return print_function(boost::bind(&printBridgeRuleEntryAsASPHelperAtom, _1, prefix, entry));
}

}  // END namespace mcsdiagexpl
} // END namespace dlvhex
#endif // _DLVHEX_MCSDIAGEXPL_BRIDGERULEENTRY_H
