#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "Converter.h"
#include "SpiritDebugging.h"
#include "BridgeRuleEntry.h"

#include <climits>
#include <sstream>
#include <cstdlib>

#include <iostream>
#include <string>
#include <ostream>
#include <vector>

namespace dlvhex {
  namespace mcsequilibrium {

   Converter::Converter() {
     // init
   }

   void
   Converter::convertBridgeRuleElem(node_t& at, int& id, std::string& fact) {
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
   Converter::convertBridgeRule(node_t& at, BridgeRule& brule) {
     int id;
     std::string f;
     for (node_t::tree_iterator ait = at.children.begin(); ait != at.children.end(); ++ait) {
	node_t& bat = *ait;
       if (bat.value.id() == MCSdescriptionGrammar::RuleHeadElem) {
         #ifdef DEBUG
           printSpiritPT(std::cout, bat, "HeadElem");
         #endif
         assert(bat.children.size()==2);
	 convertBridgeRuleElem(bat,id,f);
	 brule.setHeadRule(id,f);
         //std::cout << "Childrensize: " << bat.children.size() << "\n";
       }//end if-rule bridgeruleheadelem
       ////////////////////////////////////////////
       // there are more than 1 rule in the body //
       ////////////////////////////////////////////
       if (bat.value.id() == MCSdescriptionGrammar::RuleBody) {
	 std::cout << "RuleBody" << std::endl;
         for (node_t::tree_iterator bit = bat.children.begin(); bit != bat.children.end(); ++bit) {
           node_t& bbeat = *bit;
           if (bbeat.value.id() == MCSdescriptionGrammar::RuleElem) {
             #if 0
               printSpiritPT(std::cout, bbeat, "RuleBodyElem");
             #endif
             assert(bbeat.children.size()==2);
             convertBridgeRuleElem(bbeat,id,f);
	     brule.addBodyRule(id,f,false);
             //std::cout << "Childrensize: " << bbeat.children.size() << "\n";
           }//end if-rule for RuleElem in BridgeRuleBody
           if (bbeat.value.id() == MCSdescriptionGrammar::NegRuleElem) {
	     #if 0
               printSpiritPT(std::cout, bbeat, "NegatedRuleBodyElem");
	     #endif
             assert(bbeat.children.size()==2);
             convertBridgeRuleElem(bbeat,id,f);
	     brule.addBodyRule(id,f,true);
             //std::cout << "Childrensize: " << bbeat.children.size() << "\n";
           }//end if-rule for negated RuleElem in BridgeRuleBody
         }// end for-loop over RuleBodyElems
       }//end if-rule RuleBodyElems

       ////////////////////////////////////////////
       // there is only 1 rule in the body       //
       ////////////////////////////////////////////
       if (bat.value.id() == MCSdescriptionGrammar::RuleElem) {
         #if 0
           printSpiritPT(std::cout, bat, "RuleBodyElem");
         #endif
         assert(bat.children.size()==2);
         convertBridgeRuleElem(bat,id,f);
	 brule.addBodyRule(id,f,false);
         //std::cout << "Childrensize: " << bbeat.children.size() << "\n";
       }//end if-rule for RuleElem in BridgeRuleBody
       if (bat.value.id() == MCSdescriptionGrammar::NegRuleElem) {
	 #if 0
           printSpiritPT(std::cout, bat, "NegatedRuleBodyElem");
	 #endif
         assert(bat.children.size()==2);
         convertBridgeRuleElem(bat,id,f);
	 brule.addBodyRule(id,f,true);
         //std::cout << "Childrensize: " << bbeat.children.size() << "\n";
       }//end if-rule for negated RuleElem in BridgeRuleBody

     } //end for-loop over bridgerules
   }// End MCSequilibriumConverter::convertBridgeRule()

   void
   Converter::convertContext(node_t& at, ParseContext& context) {
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
     context = ParseContext(id,extatom,param);
     //std::cout << context;
   }// END MCSequilibriumConverter::convertContext

   void
   Converter::convertParseTreeToDLVProgram(node_t& node, std::ostream& o) {
     if (!(node.value.id() == MCSdescriptionGrammar::Root)) {
       throw PluginError("MCS Equilibrium Plugin: Inputfile syntax error!");
     }
     bridgerules.clear();
     context.clear();

     for (node_t::tree_iterator it = node.children.begin(); 
       it != node.children.end(); ++it) {
       node_t& at = *it;
       /*if ((at.value.id() != MCSdescriptionGrammar::BridgeRule) &&
         (at.value.id() != MCSdescriptionGrammar::Context))
         continue;*/
       if (at.value.id() == MCSdescriptionGrammar::BridgeRule) {
	 #ifdef DEBUG
           printSpiritPT(std::cout, at, "BridgeRule");
	 #endif
         //create new Bridgerule elem and fill the vector with elements
	 BridgeRule bridgeRule = BridgeRule();
         convertBridgeRule(at,bridgeRule);
	 //bridgeRule.writeProgram(std::cout);
         bridgerules.push_back(bridgeRule);
       } //end if-rule Bridgerule
       if (at.value.id() == MCSdescriptionGrammar::Context) {
         ParseContext c = ParseContext();
         convertContext(at,c);
         context.push_back(c);
	 #ifdef DEBUG
	   printSpiritPT(std::cout, at, "Context");
         #endif
       } //end if-rule Context		
     } // end for-loop over all children of root
     //std::cout << "Number of BridgeRules: " << bridgerules.size() << "\n";
     for (std::vector<BridgeRule>::iterator it = bridgerules.begin(); it != bridgerules.end(); ++it) {
	BridgeRule elem = *it;
	elem.writeProgram(o);
     }//end for-loop print bridgerules
     for (std::vector<ParseContext>::iterator it = context.begin(); it != context.end(); ++it) {
	ParseContext elem = *it;
	o << elem;
     }//end for-loop print context
   } // end convertParseTreeToDLVProgram

   void
   Converter::convert(std::istream& i, std::ostream& o) {
     MCSdescriptionGrammar mcsdgram;
     std::ostringstream buf;
     buf << i.rdbuf();
     std::string input = buf.str();

     iterator_t it_begin = input.c_str();
     iterator_t it_end = input.c_str() + input.size();

     tree_parse_info<iterator_t, factory_t> info = 
       ast_parse<factory_t>(it_begin, it_end, mcsdgram, space_p);

     if (!info.full) {
       throw PluginError("MCS Equilibrium Plugin: Inputfile syntax error!");
     }

     // if there's not 1 tree in the result of the parser, this is a bug
     assert(info.trees.size() == 1);

     // Convert the Parse Tree to a asp program
     stringstream ss;
     convertParseTreeToDLVProgram(*info.trees.begin(), ss);

     #ifdef DEBUG
       std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
       std::cout << "Converted DLV Program: " << std::endl;
       std::cout << ss.str();
       std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
     #endif
     o << ss.rdbuf();
     //o << "true.";// << std::endl << "b." << std::endl << "c.";	
   } // end of MCSequilibriumConverter::convert

  } // namespace script
} // namespace dlvhex
