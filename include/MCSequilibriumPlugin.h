/* dlvhex-dlplugin -- Integration of Answer-Set Programming and Description Logics.
 *
 * Copyright (C) 2005, 2006, 2007  Thomas Krennwallner
 * 
 * This file is part of dlvhex-dlplugin.
 *
 * dlvhex-dlplugin is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * dlvhex-dlplugin is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dlvhex-dlplugin; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


/*
 *  @file	MCSequilibriumPlugin.h
 *  @author	Markus Boegl
 *  @date
 *
 */

#ifndef _DLVHEX_MCSEQUILIBRIUM_MCSEQUILIBRIUMPLUGIN_H
#define _DLVHEX_MCSEQUILIBRIUM_MCSEQUILIBRIUMPLUGIN_H

#include <dlvhex/PluginInterface.h>
#include <Converter.h>
#include <MCSequilibriumAtom.h>

namespace dlvhex {
	namespace mcsequilibrium {
	
	class MCSequilibriumPlugin : public PluginInterface {
		private:
			/**
			 *
			 */
			Converter* mcseconverter;
			
			/**
			 *
			 */
			MCSequilibriumPlugin(const MCSequilibriumPlugin&);
			
			
			/**
			 *
			 */
			bool activatePlugin;
			
			
		public:

			/**
			 *
			 */
			MCSequilibriumPlugin();

			/**
			 *
			 */
			~MCSequilibriumPlugin();
			
			/**
			 *
			 */
			virtual PluginConverter* createConverter();
			
			/**
			 * Add new MCSequilibrium external atoms with the according names to m.
			 *
			 * @param m
			 */
			virtual void getAtoms(AtomFunctionMap& m);
			
			/**
			 * Set the command line arguments here.
			 *
			 * @param doHelp
			 * @param argv 
			 * @param out
			 */
			virtual void setOptions(bool doHelp, std::vector<std::string>& argv,
						std::ostream& out);
			
	
	}; // END class MCSequilibriumPlugin
	} // END namespace mcsequilibrium
} // END namespace dlvhex

#endif /* _DLVHEX_MCSEQUILIBRIUMPLUGIN_H */
