/**
 * @file   BaseContextPlugin.cpp
 * @author Peter Schueller
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "BaseContextPlugin.h"
#include "BaseContextAtom.h"
#include "ProgramCtxData.h"

#include <dlvhex2/ProgramCtx.h>

namespace dlvhex {
namespace mcsdiagexpl {

BaseContextPlugin::BaseContextPlugin()
{
}

BaseContextPlugin::~BaseContextPlugin()
{
}

std::vector<PluginAtomPtr>
BaseContextPlugin::createAtoms(ProgramCtx& ctx) const
{
  MCSIE::CtxData& pcd = ctx.getPluginData<MCSIE>();
  if( pcd.isEnabled() )
  {
    registerAtoms(pcd);
    // convert and copy to temporary
    std::vector<PluginAtomPtr> ret(
        pcd.getContextAtoms().begin(), pcd.getContextAtoms().end());
    return ret;
  }
  else
  {
    return std::vector<PluginAtomPtr>();
  }
}

} // namespace mcsequilibrium
} // namespace dlvhex

// vim:ts=8:
