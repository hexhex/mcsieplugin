/* dlvhex-mcs-equilibrium-plugin -- Inconsistency analysis and equilibrium
 * semantics for heterogeneous nonmonotonic Multi-Context Systems in dlvhex.
 * Copyright (C) 2009,2010 Markus Boegl
 * Copyright (C) 2011 Gerald Weidinger
 * Copyright (C) 2012 Peter Schueller
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
 * @file   	ProgramCtxData.h
 * @author 	Markus Boegl
 * @author 	Peter Schueller
 * 
 * @brief   Stores configuration of plugin in ProgramCtx
 */

#ifndef _DLVHEX_MCSDIAGEXPL_PROGRAMCTXDATA_H_
#define _DLVHEX_MCSDIAGEXPL_PROGRAMCTXDATA_H_

#include <dlvhex2/PluginInterface.h>
#include "MCS.h"

#include <ostream>
#include <sstream>
#include <list>

namespace dlvhex
{
namespace mcsdiagexpl
{

class BaseContextAtom;
typedef boost::shared_ptr<BaseContextAtom>
        ContextAtomPtr;

// this class serves as a wrapper around CtxData
// it is independent from MCSIEPlugin
// 
// this way, MCSIEPlugin and all plugins implementing contexts
// can share a global MCSIE configuration using
// ProgramCtx& ctx;
// MCSIE::CtxData& pcd = ctx.getPluginData<MCSIE>();
class MCSIE
{
public:
  // an alias for this class is 
  // ProgramCtxData
  // (typedef after this class)
  class CtxData:
    public ::dlvhex::PluginData
  {
  public:
    enum Mode { DIAGREWRITING, EXPLREWRITING, EQREWRITING };

  public:
    CtxData();
    virtual ~CtxData();

    bool isEnabled() const   { return enabled; }
    bool isDiag() const      { return diagnose; }
    bool isminDiag() const   { return mindiag; }
    bool isExp() const       { return explanation; }
    bool isminExp() const    { return minexpl; }
    bool isprintOPEQ() const { return printopeq; }
    Mode getMode() const     { return mode; }

    void setEnabled();
    void setDiag();
    void setExp();
    void setminExp();
    void setminDiag();
    void setprintOPEQ(bool to=true);
    void setMode(Mode mode);

    const std::vector<ContextAtomPtr>& getContextAtoms() const
      { return contextAtoms; }
    std::vector<ContextAtomPtr>& getContextAtoms()
      { return contextAtoms; }

    const MCS& mcs() const
      { return mcs_; }
    MCS& mcs()
      { return mcs_; }

    const std::string& path() const
      { return path_; }
    void setPath(const std::string& path)
      { path_ = path; }

  protected:
    // whether plugin is enabled
    bool enabled;
    // how to calculate
    Mode mode;
    // what to display/calculate
    bool diagnose, explanation, mindiag, minexpl, printopeq;

    // path prefix
    std::string path_;

    // MCSIE context atoms registered by MCSIE and MCSIE plugins
    std::vector<ContextAtomPtr> contextAtoms;

    // parsed MCS representation
    MCS mcs_;
  };
};
typedef MCSIE::CtxData
  ProgramCtxData;

}
}

#endif /* _DLVHEX_MCSDIAGEXPL_PROGRAMCTXDATA_H_ */
