#ifndef _DLVHEX_MCSEQUILIBRIUMCONVERTER_H_
#define _DLVHEX_MCSEQUILIBRIUMCONVERTER_H_

#include <dlvhex/PluginInterface.h>

#include <MCSequilibriumParserDriver.h>


namespace dlvhex {
	namespace mcsequilibrium {

	class MCSequilibriumConverter : public PluginConverter {
		public:
    			MCSequilibriumConverter();

    			virtual void convert(std::istream& i, std::ostream& o);

	}; // END class MCSequilibriumConverter
	}  // END namespace mcsequilibrium
} // END namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUMCONVERTER_H
