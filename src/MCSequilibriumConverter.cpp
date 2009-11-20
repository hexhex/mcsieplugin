#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "MCSequilibriumConverter.h"
#include "SpiritDebugging.h"
#include "MCSequilibriumBridgeRuleEntry.h"

#include <climits>
#include <sstream>
#include <cstdlib>

#include <iostream>
#include <string>
#include <ostream>
#include <vector>

namespace dlvhex {
  namespace mcsequilibrium {

   MCSequilibriumConverter::MCSequilibriumConverter() {
     // init
   }

   void
   MCSequilibriumConverter::convertBridgeRuleElem(node_t& at, int& id, std::string& fact) {
        node_t* n = &at;
	node_t::tree_iterator it = at.children.begin();
	node_t& bat = *it;
	assert(bat.value.id() == MCSdescriptionGrammar::RuleNum);
        id = atoi(std::string(bat.value.begin(), bat.value.end()).c_str());
	++it;
	bat = *it;
	assert(bat.value.id() == MCSdescriptionGrammar::Fact);
        fact = std::string(bat.value.begin(), bat.value.end());
   } // end convertBridgeRuleElem

   void
   MCSequilibriumConverter::convertBridgeRule(node_t& at, MCSequilibriumBridgeRule& brule) {
     int id;
     std::string f;
     for (node_t::tree_iterator ait = at.children.begin(); ait != at.children.end(); ++ait) {
       node_t& bat = *ait;
       if (bat.value.id() == MCSdescriptionGrammar::RuleHeadElem) {
         //printSpiritPT(std::cout, bat, "HeadElem");
         assert(bat.children.size()==2);
	 convertBridgeRuleElem(bat,id,f);
	 brule.setHeadRule(id,f);
         //std::cout << "Childrensize: " << bat.children.size() << "\n";
       }//end if-rule bridgeruleheadelem
       if (bat.value.id() == MCSdescriptionGrammar::RuleBody) {
         for (node_t::tree_iterator bit = bat.children.begin(); bit != bat.children.end(); ++bit) {
           node_t& bbeat = *bit;
           if (bbeat.value.id() == MCSdescriptionGrammar::RuleElem) {
             //printSpiritPT(std::cout, bbeat, "RuleBodyElem");
             assert(bbeat.children.size()==2);
             convertBridgeRuleElem(bbeat,id,f);
	     brule.addBodyRule(id,f,false);
             //std::cout << "Childrensize: " << bbeat.children.size() << "\n";
           }//end if-rule for RuleElem in BridgeRuleBody
           if (bbeat.value.id() == MCSdescriptionGrammar::NegRuleElem) {
             //printSpiritPT(std::cout, bbeat, "NegatedRuleBodyElem");
             assert(bbeat.children.size()==2);
             convertBridgeRuleElem(bbeat,id,f);
	     brule.addBodyRule(id,f,true);
             //std::cout << "Childrensize: " << bbeat.children.size() << "\n";
           }//end if-rule for negated RuleElem in BridgeRuleBody
         }// end for-loop over RuleBodyElems
       }//end if-rule RuleBodyElems
     } //end for-loop over bridgerules
   }// End MCSequilibriumConverter::convertBridgeRule()

   void
   MCSequilibriumConverter::convertContext(node_t& at, MCSequilibriumContext& context) {
     int id;
     std::string extatom;
     std::string param;

     assert(at.children.size() == 3);
     node_t::tree_iterator it = at.children.begin();
     node_t& bat = *it;
     assert(bat.value.id() == MCSdescriptionGrammar::ContextNum);
     id = atoi(std::string(bat.value.begin(), bat.value.end()).c_str());
     ++it;
     bat = *it;
     assert(bat.value.id() == MCSdescriptionGrammar::ExtAtom);
     extatom = std::string(bat.value.begin(), bat.value.end());
     ++it;
     bat = *it;
     assert(bat.value.id() == MCSdescriptionGrammar::Param);
     param = std::string(bat.value.begin(), bat.value.end());
     context = MCSequilibriumContext(id,extatom,param);
     //std::cout << context;
   }// END MCSequilibriumConverter::convertContext

   void
   MCSequilibriumConverter::convertParseTreeToDLVProgram(node_t& node, std::ostream& o) {
     assert(node.value.id() == MCSdescriptionGrammar::Root);
     bridgerules.clear();
     context.clear();

     for (node_t::tree_iterator it = node.children.begin(); 
       it != node.children.end(); ++it) {
       node_t& at = *it;
       /*if ((at.value.id() != MCSdescriptionGrammar::BridgeRule) &&
         (at.value.id() != MCSdescriptionGrammar::Context))
         continue;*/
       if (at.value.id() == MCSdescriptionGrammar::BridgeRule) {
         //printSpiritPT(std::cout, at, "BridgeRule");
         //create new Bridgerule elem and fill the vector with elements
	 MCSequilibriumBridgeRule bridgeRule = MCSequilibriumBridgeRule();
         convertBridgeRule(at,bridgeRule);
	 //bridgeRule.writeProgram(std::cout);
         bridgerules.push_back(bridgeRule);
       } //end if-rule Bridgerule
       if (at.value.id() == MCSdescriptionGrammar::Context) {
         MCSequilibriumContext c = MCSequilibriumContext();
         convertContext(at,c);
         context.push_back(c);
	 //printSpiritPT(std::cout, at, "Context");
       } //end if-rule Context		
     } // end for-loop over all children of root
     //std::cout << "Number of BridgeRules: " << bridgerules.size() << "\n";
     for (std::vector<MCSequilibriumBridgeRule>::iterator it = bridgerules.begin(); it != bridgerules.end(); ++it) {
	MCSequilibriumBridgeRule elem = *it;
	elem.writeProgram(o);
     }//end for-loop print bridgerules
     for (std::vector<MCSequilibriumContext>::iterator it = context.begin(); it != context.end(); ++it) {
	MCSequilibriumContext elem = *it;
	o << elem;
     }//end for-loop print context
   } // end convertParseTreeToDLVProgram

   void
   MCSequilibriumConverter::convert(std::istream& i, std::ostream& o) {
     MCSdescriptionGrammar mcsdgram;
     std::ostringstream buf;
     buf << i.rdbuf();
     std::string input = buf.str();

     iterator_t it_begin = input.c_str();
     iterator_t it_end = input.c_str() + input.size();
     /*boost::spirit::tree_parse_info<> info = 
       boost::spirit::pt_parse(inputcontent.str().c_str(), 
       inputcontent.str().c_str()+inputcontent.str().size(), 
       mcsdgram, boost::spirit::space_p);
*/
     //parse_info<> info = parse(inputcontent.str().c_str(), mcsdgram, space_p);
     tree_parse_info<iterator_t, factory_t> info = 
       ast_parse<factory_t>(it_begin, it_end, mcsdgram, space_p);
     // pt_parse<factory_t>(inputcontent.str().c_str(), inputcontent.str().c_str()+inputcontent.str().size(), mcsdgram, space_p);

    /* std::cout << "match: ";
     if (info.match) std::cout << "true\n";
     else std::cout << "false\n";
     std::cout << "full: ";
     if (info.full) std::cout << "true\n";
     else std::cout << "false\n"; */

     if (!info.full) {
       throw PluginError("MCS Equilibrium Plugin: Inputfile syntax error!");
     }

     //printSpiritPT(std::cout, *info.trees.begin(), "");
     //std::cout << "Treesize: " << info.trees.size() << "\n";

     // if there's not 1 tree in the result of the parser, this is a bug
     assert(info.trees.size() == 1);
     //o << i;

     // Convert the Parse Tree to a asp program
     std::cout << "Converted DLV Program: " << std::endl;
     convertParseTreeToDLVProgram(*info.trees.begin(), std::cout);
     o << "true.";// << std::endl << "b." << std::endl << "c.";	
   } // end of MCSequilibriumConverter::convert

  } // namespace script
} // namespace dlvhex
