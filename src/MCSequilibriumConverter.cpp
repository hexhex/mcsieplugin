#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSequilibriumConverter.h"

#include <climits>
#include <sstream>
#include <cstdlib>


namespace dlvhex {
  namespace mcsequilibrium {

	MCSequilibriumConverter::MCSequilibriumConverter() {
		// init
	}

	void
	MCSequilibriumConverter::convert(std::istream& i, std::ostream& o) {
		std::ostringstream inputcontent;
		std::string line;
		while (!i.eof()) {
			std::getline(i, line);
			inputcontent << line << std::endl;
		}

		MCSdescriptionGrammar mcsdgram;
		boost::spirit::parse_info<> info = boost::spirit::parse(inputcontent.str().c_str(), mcsdgram, boost::spirit::space_p);
		if (!info.full) {
			throw PluginError("MCS Equilibrium syntax error!");
		}

		//o << i;
		o << "true.";// << std::endl << "b." << std::endl << "c.";	
	}

  } // namespace script
} // namespace dlvhex
