#ifndef _DLVHEX_MCSEQUILIBRIUM_MCSEQUILIBRIUMPLUGIN_H_
#define _DLVHEX_MCSEQUILIBRIUM_MCSEQUILIBRIUMPLUGIN_H_

#include <dlvhex/ProgramCtx.h>
#include "Converter.h"
#include "EquilibriumOutputBuilder.h"
#include "DLV_ASP_ContextAtom.h"
#include "BaseContextPlugin.h"

namespace dlvhex {
  namespace mcsequilibrium {
	
    class MCSequilibriumPlugin : public BaseContextPlugin {
	private:
	  Converter* mcseconverter;
	  OutputBuilder* equilibriumOB;
	  MCSequilibriumPlugin(const MCSequilibriumPlugin&);
	  bool activatePlugin;
	  AtomFunctionMap *afm;

	public:
	  MCSequilibriumPlugin();
	  ~MCSequilibriumPlugin();
	  virtual void setupProgramCtx(ProgramCtx& pc);
	  virtual OutputBuilder* createOutputBuilder();
	  virtual PluginConverter* createConverter();
	  virtual void registerAtoms();
	
    }; // END class MCSequilibriumPlugin
  } // END namespace mcsequilibrium
} // END namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUM_MCSEQUILIBRIUMPLUGIN_H_
