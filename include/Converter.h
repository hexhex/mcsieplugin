#ifndef _DLVHEX_MCSEQUILIBRIUM_CONVERTER_H_
#define _DLVHEX_MCSEQUILIBRIUM_CONVERTER_H_

#include <dlvhex/PluginInterface.h>
#include "ParserDriver.h"
#include "BridgeRule.h"
#include "Context.h"

#include <vector>

namespace dlvhex {
	namespace mcsequilibrium {

	class Converter : public PluginConverter {
		public:

			typedef boost::spirit::node_val_data_factory<> factory_t;
			typedef const char* iterator_t;
			// node type for spirit PT
			typedef boost::spirit::tree_match<iterator_t, factory_t>::node_t node_t;

    			Converter();

    			virtual void convert(std::istream& i, std::ostream& o);
		private:
			std::vector<BridgeRule> bridgerules;
			std::vector<Context> context;
			void convertParseTreeToDLVProgram(node_t& node, std::ostream& o);
			void convertBridgeRule(node_t& at, BridgeRule& brule);
			void convertBridgeRuleElem(node_t& at, int& id, std::string& fact);
			void convertContext(node_t& at, Context& context);

	}; // END class Converter
	}  // END namespace mcsequilibrium
} // END namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUM_CONVERTER_H
