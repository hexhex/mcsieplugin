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
 * @file   	BridgeRule.h
 * @author 	Markus Boegl
 * @author 	Gerald Weidinger
 * @author 	Peter Schueller
 * @date   	Sun Feb 24 13:32:05 2011
 * 
 * @brief       Bridge rule representation
 */
#ifndef _DLVHEX_MCSDIAGEXPL_BRIDGERULE_H_
#define _DLVHEX_MCSDIAGEXPL_BRIDGERULE_H_

#include "BridgeRuleEntry.h"

#include <dlvhex2/Printhelpers.h>

#include <vector>
#include <string>

namespace dlvhex {
namespace mcsdiagexpl {

class BridgeRule:
  public ostream_printable<BridgeRule>
{
  BridgeRuleEntry head;
  std::vector<BridgeRuleEntry> body;
  bool fact;
  std::string ruleid;

public:
  BridgeRule(bool f);
  BridgeRule();
  void setHeadRule(std::string rid, int cid, std::string f);
  void addBodyRule(int id, std::string f, bool n);

  const BridgeRuleEntry& Head() const { return head; }
  const std::vector<BridgeRuleEntry>& Body() const { return body; }
  const std::string& Id() const { return ruleid; }

  std::ostream& print(std::ostream&) const;
};

typedef std::vector<BridgeRuleEntry>::const_iterator BridgeRuleEntryIterator;

}  // END namespace mcsdiagexpl
} // END namespace dlvhex

#endif // _DLVHEX_MCSDIAGEXPL_BRIDGERULE_H_
