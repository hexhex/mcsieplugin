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
 * @file   MCSequilibriumPlugin.cpp
 * @author Markus Boegl
 * @date   Sun Jan 24 13:45:07 2010
 * 
 * @brief  Main Class of dlvhex-mcs-equilibrium-plugin
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSdiagexplPlugin.h"
#include "Timing.h"
#include "Global.h"


namespace dlvhex {
  namespace mcsdiagexpl {

MCSdiagexplPlugin::MCSdiagexplPlugin()
    : activatePlugin(1), mcseconverter(new QiConverter()), equilibriumOB(new EquilibriumOutputBuilder()) {
    //(Timing::getInstance())->begin();
}


MCSdiagexplPlugin::~MCSdiagexplPlugin() {
    delete mcseconverter;
    // do not delete the equilibriumOB here because the
    // OutputBuilder will be deleted by dlvhex
    // and if you delete it here, there will be an error
}

void
MCSdiagexplPlugin::setupProgramCtx(dlvhex::ProgramCtx& pc) {
	pc.setOutputBuilder(equilibriumOB);
	if((Timing::getInstance())->isActive()) {
		(Timing::getInstance())->begin();
	}
}

OutputBuilder*
MCSdiagexplPlugin::createOutputBuilder() {
   return equilibriumOB;
}


PluginConverter*
MCSdiagexplPlugin::createConverter() {
    if (!this->activatePlugin) {
        return 0;
    }
    return mcseconverter;
}

void 
MCSdiagexplPlugin::registerAtoms() {
   registerAtom<DLV_ASP_ContextAtom>();
}

	void 
	MCSdiagexplPlugin::setOptions(bool doHelp, std::vector<std::string>& argv, std::ostream& out) {
	    std::string::size_type o;
	    std::vector<std::vector<std::string>::iterator> found;

	    if (doHelp) {
	       //      123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-
	        out << "Diagnosis and Explanation calculation Plugin: " << std::endl << std::endl;
	        out << " --explain={D, Dm, E, Em} " << std::endl;
	        out << " --noprintopeq            " << std::endl;
	        out << " --benchmark              " << std::endl;
		out << std::endl;
	        return;
	    }

	    for (std::vector<std::string>::iterator it = argv.begin();
		it != argv.end(); ++it) {

	        o = it->find("--explain=");
	        if (o != std::string::npos) {
	        	std::string expl = (it->substr(10));
	        	bool f = false;
	        	if (expl.compare("D") == 0) {
	        		(Global::getInstance())->setDiag();
	        		f = true;
	        	}
	        	if (expl.compare("E") == 0) {
	        		(Global::getInstance())->setExp();
	        		f = true;
	        	}
	        	if (expl[2] == 'm') {
	        		(Global::getInstance())->setMin();
	        		f = true;
	        	}
	        	if (f)
	        		found.push_back(it);
	        	continue;
	        }

	        o = it->find("--noprintopeq");
	        if (o != std::string::npos) {
	        	found.push_back(it);
	        	continue;
	        }

	        o = it->find("--benchmark");
	        if (o != std::string::npos) {
	        	found.push_back(it);
	        	bench=true;
	        	(Timing::getInstance())->activate();
	        	continue;
	        }
	    }

	    for (std::vector<std::vector<std::string>::iterator>::const_iterator it =
	         found.begin(); it != found.end(); ++it) {
	        argv.erase(*it);
	    }
	}

    MCSdiagexplPlugin theMCSdiagexplPlugin;

  } // namespace mcsequilibrium
} // namespace dlvhex

extern "C"
dlvhex::mcsdiagexpl::MCSdiagexplPlugin*
PLUGINIMPORTFUNCTION() {
  dlvhex::mcsdiagexpl::theMCSdiagexplPlugin.setPluginName(PACKAGE_TARNAME);
  dlvhex::mcsdiagexpl::theMCSdiagexplPlugin.setVersion(MCSDIAGEXPLPLUGIN_MAJOR,
					     MCSDIAGEXPLPLUGIN_MINOR,
					     MCSDIAGEXPLPLUGIN_MICRO);

  return &dlvhex::mcsdiagexpl::theMCSdiagexplPlugin;
}
