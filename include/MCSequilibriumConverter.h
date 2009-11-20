#ifndef _DLVHEX_MCSEQUILIBRIUMCONVERTER_H_
#define _DLVHEX_MCSEQUILIBRIUMCONVERTER_H_

#include <dlvhex/PluginInterface.h>
#include <MCSequilibriumParserDriver.h>
#include <MCSequilibriumBridgeRule.h>
#include <MCSequilibriumContext.h>

#include <vector>

namespace dlvhex {
	namespace mcsequilibrium {

	class MCSequilibriumConverter : public PluginConverter {
		public:

			typedef boost::spirit::node_val_data_factory<> factory_t;
			typedef const char* iterator_t;
			// node type for spirit PT
			typedef boost::spirit::tree_match<iterator_t, factory_t>::node_t node_t;

    			MCSequilibriumConverter();

    			virtual void convert(std::istream& i, std::ostream& o);
		private:
			std::vector<MCSequilibriumBridgeRule> bridgerules;
			std::vector<MCSequilibriumContext> context;
			void convertParseTreeToDLVProgram(node_t& node, std::ostream& o);
			void convertBridgeRule(node_t& at, MCSequilibriumBridgeRule& brule);
			void convertBridgeRuleElem(node_t& at, int& id, std::string& fact);
			void convertContext(node_t& at, MCSequilibriumContext& context);

	}; // END class MCSequilibriumConverter
	}  // END namespace mcsequilibrium
} // END namespace dlvhex

#endif // _DLVHEX_MCSEQUILIBRIUMCONVERTER_H
