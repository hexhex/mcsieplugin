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
 * @file   MCSIEPlugin.cpp
 * @author Markus Boegl
 * @author Gerald Weidinger
 * @author Peter Schueller
 * @date   Sun Dez 24 13:45:07 2010
 * 
 * @brief  Main Class of dlvhex-mcs-equilibrium-plugin
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSIEPlugin.h"
#include "ProgramCtxData.h"
#include "SaturationMetaAtom.h"
#include "DLV_ASP_ContextAtom.h"
#include "InputConverterDiagnoses.h"
#include "InputConverterExplanations.h"
#include "InputConverterOPEquilibria.h"
#include "PrintAndAccumulateModelCallback.h"
#include "MinPrintDualConvertFinalCallback.h"

#include <dlvhex2/ProgramCtx.h>
#include <dlvhex2/PredicateMask.h>
#include <dlvhex2/Logger.h>

#include <boost/algorithm/string.hpp>

namespace dlvhex {
namespace mcsdiagexpl {

MCSIEPlugin::MCSIEPlugin()
{
  setNameVersion(PACKAGE_TARNAME,
      MCSIEPLUGIN_VERSION_MAJOR,
      MCSIEPLUGIN_VERSION_MINOR,
      MCSIEPLUGIN_VERSION_MICRO);
}


MCSIEPlugin::~MCSIEPlugin()
{
}

// change model callback
void MCSIEPlugin::setupProgramCtx(ProgramCtx& ctx)
{
  ProgramCtxData& pcd = ctx.getPluginData<MCSIE>();
  if( pcd.isEnabled() )
  {
    // setup predicate masks

    RegistryPtr reg(ctx.registry());

    // store registry in ProgramCtxData
    pcd.reg = reg;

    // configure predicate mask for d1/d2
    pcd.brdmask.setRegistry(reg);
    pcd.idd1 = reg->storeConstantTerm("d1");
    pcd.idd2 = reg->storeConstantTerm("d2");
    pcd.brdmask.addPredicate(pcd.idd1);
    pcd.brdmask.addPredicate(pcd.idd2);

    // configure predicate mask for e1/e2
    pcd.bremask.setRegistry(reg);
    pcd.ide1 = reg->storeConstantTerm("e1");
    pcd.ide2 = reg->storeConstantTerm("e2");
    pcd.bremask.addPredicate(pcd.ide1);
    pcd.bremask.addPredicate(pcd.ide2);

    // configure predicate mask for each context's output beliefs
    assert(!pcd.mcs().contexts.empty() &&
           "here we expect to have parsed the input and "
           "we expect to know the number of contexts");
    for(ContextIterator it = pcd.mcs().contexts.begin();
        it != pcd.mcs().contexts.end(); ++it)
    {
      pcd.obmasks.push_back(PredicateMask());
      PredicateMask& mask = pcd.obmasks.back();

      std::ostringstream s;
      s << "a" << it->ContextNum();

      mask.setRegistry(reg);
      ID idob(reg->storeConstantTerm(s.str()));
      mask.addPredicate(idob);
    }

    // register model callbacks (accumulate minimal notions, print nonminimal notions)
    PrintAndAccumulateModelCallback* ppcd =
        new PrintAndAccumulateModelCallback(pcd);
		ModelCallbackPtr mcb(ppcd);
		#warning here we could try to only remove the default answer set printer
		ctx.modelCallbacks.clear();
		ctx.modelCallbacks.push_back(mcb);

    // register final callback (print minmimal notions, convert to dual notions)
    switch(pcd.getMode())
    {
    case ProgramCtxData::DIAGREWRITING:
      {
        FinalCallbackPtr fcb(new DiagRewritingFinalCallback(pcd, *ppcd));
        ctx.finalCallbacks.push_back(fcb);
      }
      break;
    case ProgramCtxData::EXPLREWRITING:
      {
        FinalCallbackPtr fcb(new ExplRewritingFinalCallback(pcd, *ppcd));
        ctx.finalCallbacks.push_back(fcb);
      }
      break;
    // do nothing for eq mode
    }
  }
}

PluginConverterPtr
MCSIEPlugin::createConverter(ProgramCtx& ctx)
{
  ProgramCtxData& pcd = ctx.getPluginData<MCSIE>();
  if( pcd.isEnabled() )
  {
    switch(pcd.getMode())
    {
    case ProgramCtxData::DIAGREWRITING:
      return PluginConverterPtr(new InputConverterDiagnoses(pcd));
    case ProgramCtxData::EXPLREWRITING:
      return PluginConverterPtr(new InputConverterExplanations(pcd));
    case ProgramCtxData::EQREWRITING:
      return PluginConverterPtr(new InputConverterOPEquilibria(pcd));
    default:
      throw PluginError("MCSIEPlugin::createConverter encountered unknown mode!");
    }
  }
  else
  {
    return PluginConverterPtr();
  }
}

void 
MCSIEPlugin::registerAtoms(ProgramCtxData& pcd) const
{
  // register the only context type we directly provide in this plugin
  registerAtom<DLV_ASP_ContextAtom>(pcd);
}

// we do not only provide context atoms, so we also need to override the following
std::vector<PluginAtomPtr>
MCSIEPlugin::createAtoms(ProgramCtx& ctx) const
{
  MCSIE::CtxData& pcd = ctx.getPluginData<MCSIE>();
  if( pcd.isEnabled() )
  {
    // get context atoms
    std::vector<PluginAtomPtr> atoms(
        BaseContextPlugin::createAtoms(ctx));

    // register additional atoms
    atoms.push_back(PluginAtomPtr(new SaturationMetaAtom));
    return atoms;
  }
  else
  {
    return std::vector<PluginAtomPtr>();
  }
}

void
MCSIEPlugin::printUsage(std::ostream& out) const
{
  //      123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-
  out << "     MCS Inconsistency Explainer (Diagnosis, Explanation, Equilibria)" << std::endl;
  out << "     --ieenable              Enable plugin" << std::endl;
  out << "     --iepath=<path>         Path prefix for context files" << std::endl;
  out << "     --ieexplain={D,Dm,E,Em} Select which analysis notions to compute" << std::endl;
  out << "     --ienoprintopeq         Do not print output-projected equilibria for diagnoses" << std::endl;
  out << "     --iemode={diag,expl,eq} Select mode of calculation:" << std::endl;
  out << "              diag           Rewrite to guessing diagnoses + equilibria" << std::endl;
  out << "              expl           Rewrite to saturation encoding for explanations" << std::endl;
  out << "              eq (default)   Rewrite to equilibria calculation" << std::endl;
}

void 
MCSIEPlugin::processOptions(
    std::list<const char*>& pluginOptions, ProgramCtx& ctx)
{
  MCSIE::CtxData& pcd = ctx.getPluginData<MCSIE>();
  std::vector<std::list<const char*>::iterator> found;
  std::string option;

  // check whether any mode is set
  bool nomode = true;
  
  for(std::list<const char*>::iterator it = pluginOptions.begin(); 
      it != pluginOptions.end(); it++) 
  {
    option.assign(*it);
    if( option.find("--ieexplain=") != std::string::npos )
    {
        std::string expl = option.substr(12);
        bool f = false;
        std::vector<std::string> strs;
        boost::split(strs, expl, boost::is_any_of(","));
        for (std::vector<std::string>::const_iterator vit = strs.begin(); vit != strs.end(); ++vit) {
              if ((*vit).compare("D") == 0) {
                      pcd.setDiag();
                      f = true;
              }
              if ((*vit).compare("E") == 0) {
                      pcd.setExp();
                      f = true;
              }
              if ((*vit).compare("Dm") == 0) {
                      pcd.setminDiag();
                      f = true;
              }
              if ((*vit).compare("Em") == 0) {
                      pcd.setminExp();
                      f = true;
              }
        }
        if (f)
          found.push_back(it);
        continue;
    }

    if( option.find("--iemode=") != std::string::npos )
    {
        std::string mode = option.substr(9);
        bool f = false;
        if( mode == "diag" )
        {
          pcd.setMode(ProgramCtxData::DIAGREWRITING);
          f = true;
        }
        else if( mode == "expl" )
        {
          pcd.setMode(ProgramCtxData::EXPLREWRITING);
          f = true;
        }
        else if( mode == "eq" )
        {
          pcd.setMode(ProgramCtxData::EQREWRITING);
          f = true;
        }
        else
        {
          LOG(WARNING,"MCSIE: got unknown mode '" << mode << "'"
              " -> not processing option");
        }
        if( f )
        {
          found.push_back(it);
          nomode = false;
          continue;
        }
    }

    if( option.find("--ienoprintopeq") != std::string::npos )
    {
      pcd.setprintOPEQ(false);
      found.push_back(it);
      continue;
    }

    if( option.find("--iepath=") != std::string::npos )
    {
      std::string path = option.substr(9);
      pcd.setPath(path);
      found.push_back(it);
      continue;
    }

    /*
    if( option.find("--iebenchmark") != std::string::npos )
    {
              found.push_back(it);
              bench=true;
              (Timing::getInstance())->activate();
              continue;
    }
    */

    if( option.find("--ieenable") != std::string::npos )
    {
      pcd.setEnabled();
      found.push_back(it);
      continue;
    }
  }

  if( nomode )
  {
    if( pcd.isDiag() || pcd.isminDiag() || pcd.isExp() || pcd.isminExp() )
      // use diag rewriting if we want to get any inconsistency notions
      pcd.setMode(ProgramCtxData::DIAGREWRITING);
    else
      // otherwise use equilibrium rewriting
      pcd.setMode(ProgramCtxData::EQREWRITING);
  }

  for(std::vector<std::list<const char*>::iterator>::const_iterator it = found.begin(); 
      it != found.end(); ++it) 
  {
    pluginOptions.erase(*it);
  }
}

MCSIEPlugin theMCSIEPlugin;

} // namespace mcsdiagexpl
} // namespace dlvhex

IMPLEMENT_PLUGINABIVERSIONFUNCTION

extern "C"
void* PLUGINIMPORTFUNCTION()
{
  return reinterpret_cast<void*>(&dlvhex::mcsdiagexpl::theMCSIEPlugin);
}

// vim:ts=2:sw=2:et:
