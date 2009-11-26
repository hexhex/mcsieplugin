#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "DLV_ASP_Context.h"

#include <unistd.h>
#include <climits>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "dlvhex/ProgramCtx.h"
#include "dlvhex/DLVProcess.h"
#include "dlvhex/AtomSet.h"
#include "dlvhex/Program.h"
#include "dlvhex/ResultContainer.h"
#include "dlvhex/globals.h"
#include "dlvhex/HexParserDriver.h"
#include "dlvhex/ASPSolver.h"
#include "dlvhex/TextOutputBuilder.h"

namespace dlvhex {
  namespace mcsequilibrium {

DLV_ASP_Context::DLV_ASP_Context() : GenericContextAtom("dlv_asp") {}

set<string> 
DLV_ASP_Context::acc(const string& param, const set<string>& input) {
  set<string> ret;
  ret.insert("bcd");
  ret.insert("x");
  return ret;
} // end ACC implementation*/

void
DLV_ASP_Context::retrieve(const Query& query, Answer& answer) throw (PluginError) {

  std::set<std::string> oset,aset,bset,naset;
  set<string> interset, accset;

  const std::string param = query.getInputTuple()[4].getUnquotedString();
  convertQueryToStringSets(query,aset,bset,oset);
//  cout << "param filename: " << param << endl;

  naset = oset;
  for (set<string>::iterator strit = aset.begin(); strit != aset.end(); ++strit) {
    naset.erase(*strit);
  }
/*  cout << "NASET Size: " << naset.size() << endl;

  std::stringstream tmpin;
  std::ifstream ifs;
  ifs.open(param.c_str());

  if (!ifs.is_open())
    {
      throw GeneralError("File " + param + " not found");
    }

  tmpin << ifs.rdbuf();
  ifs.close();
  cout << "Readed Program: " << endl;
  cout << tmpin.str() << endl;
*/

  DLVProcess dlv;
  std::vector<AtomSet> answersets;
  std::vector<AtomSet>::const_iterator as;
  std::auto_ptr<BaseASPSolver> solver(dlv.createSolver());
  
  Program *idb = new Program();
  /// stores the facts of the program
  AtomSet *edb = new AtomSet();
  HexParserDriver driver;
  driver.parse(param, *idb, *edb);
//  cout << "Atomset size: " << edb->size() << endl;
  // add Atomsets
  for (set<string>::iterator inputit = bset.begin(); inputit != bset.end(); ++inputit) {
    //*inputit
    edb->insert(AtomPtr(new Atom(Tuple(1, Term(*inputit)))));
  }
//  cout << "Atomset size: " << edb->size() << endl;

  // Rules of Programm
  RuleHead_t h;
  RuleBody_t b;
  h.clear();

  for (set<string>::iterator verifyit = aset.begin(); verifyit != aset.end(); ++verifyit) {
    b.clear();
    b.insert(new Literal(AtomPtr(new Atom(*verifyit)), true));
    idb->addRule(new Rule(h,b));
  }

  for (set<string>::iterator negit = naset.begin(); negit != naset.end(); ++negit) {
    b.clear();
    b.insert(new Literal(AtomPtr(new Atom(*negit)), false));
    idb->addRule(new Rule(h,b));
  }

  solver->solve(*idb, *edb, answersets);
/*  ResultContainer* result = new ResultContainer();

  cout << "Anzahl der Answerset: " << answersets.size() << endl;
  cout << "Answerset: " << *answersets << endl;
  for (as = answersets.begin(); as!=answersets.end(); ++as) {
    cout << "Answerset size: " << as->size() << endl;
    cout << (as->getArgument(1)).getString() << endl;
    result->addSet(*as);
  }

  OutputBuilder *outputbuilder = new TextOutputBuilder();
  result->print(std::cout, outputbuilder);

  cout << "-------------------------------------------" << endl;
*/
  if (answersets.size() > 0) {
    Tuple out;
    answer.addTuple(out);
  }
}

  } // namespace script
} // namespace dlvhex
