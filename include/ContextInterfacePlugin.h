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
 * @file   ContextInterfacePlugin.h
 * @author Markus Boegl
 * @date   Sun Jan 24 13:55:42 2010
 * 
 * @brief  Interface for User implemented Plugin
 */
#ifndef _CONTEXTINTERFACEPLUGIN_H_
#define _CONTEXTINTERFACEPLUGIN_H_

#include "BaseContextPlugin.h"

#define DLVHEX_MCSEQUILIBRIUM_PLUGIN(abimajor,abiminor,abimicro,classname,major,minor,micro) \
namespace {\
  class classname : public dlvhex::mcsdiagexpl::BaseContextPlugin {\
    public:\
      typedef dlvhex::mcsdiagexpl::ProgramCtxData ProgramCtxData; \
      classname();\
      virtual void registerAtoms(ProgramCtxData& pcd) const;\
  };\
  classname::classname() { \
    setNameVersion(#classname,major,minor,micro);\
  };\
  classname thePlugin;\
}\
\
extern "C" \
int PLUGINABIVERSIONFUNCTION() \
{ \
  return abimajor*10000+abiminor*100+abimicro; \
} \
extern "C"\
void* PLUGINIMPORTFUNCTION() {\
  return reinterpret_cast<void*>(&thePlugin);\
}
#endif //_CONTEXTINTERFACEPLUGIN_H_
