#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#define DEBUG

#include "DLV_ASP_ContextAtom.h"

#include <unistd.h>
#include <climits>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "dlvhex/ProgramCtx.h"
#include "dlvhex/DLVProcess.h"
#include "dlvhex/AtomSet.h"
#include "dlvhex/Program.h"
#include "dlvhex/ResultContainer.h"
#include "dlvhex/globals.h"
#include "dlvhex/HexParserDriver.h"
#include "dlvhex/ASPSolver.h"
#include "dlvhex/TextOutputBuilder.h"
#include "dlvhex/DLVresultParserDriver.h"

namespace dlvhex {
  namespace mcsequilibrium {

using namespace std;

#if 0
set<string> 
DLV_ASP_Context::acc(const string& param, const set<string>& input) {
  set<string> ret;

  /////////////////////////////////////////////////////////////////
  //
  // Setting Up DLV Process and Options
  //
  /////////////////////////////////////////////////////////////////

  DLVProcess dlv;
  dlv.addOption("-facts");
  std::vector<AtomSet> answersets;

  std::vector<std::string> tmp;

  //tmp.push_back(DLVPATH);
  // never include the set of initial facts in the answer sets
  tmp.push_back("-silent");


  /////////////////////////////////////////////////////////////////
  //
  // Setting Up Solver
  //
  /////////////////////////////////////////////////////////////////

  // 1. Art BaseASPSolver
  std::auto_ptr<BaseASPSolver> solver(dlv.createSolver());
  // 2. Art ASPFileSolver
  //ASPFileSolver<DLVresultParserDriver> solver(dlv,tmp);
    

  Program *idb = new Program();
  /// stores the facts of the program
  AtomSet *edb = new AtomSet();
  const Program *pp = idb;
  const AtomSet *atsp = edb;


  /////////////////////////////////////////////////////////////////
  //
  // Parsing Programm
  //
  /////////////////////////////////////////////////////////////////

  //HexParserDriver driver;
  HexParserDriver driver;
  driver.parse(param, *idb, *edb);

  //DLVresultParserDriver driver;
  //driver.parse(param, 


//  cout << "Atomset size: " << edb->size() << endl;
  // add Atomsets b<i>
  for (set<string>::iterator inputit = input.begin(); inputit != input.end(); ++inputit) {
    //*inputit
    #ifdef DEBUG
      cout << "added input belief: " << *inputit << endl;
    #endif
    edb->insert(AtomPtr(new Atom(Tuple(1, Term(*inputit)))));
  }

  /////////////////////////////////////////////////////////////////
  //
  // Solve Program
  //
  /////////////////////////////////////////////////////////////////
  #ifdef DEBUG
    cout << "Start solving dlv program: " << endl;
    const Rule *r;
    int i=0;
    for (Program::const_iterator progit = idb->begin(); progit != idb->end(); ++i, ++progit) {
      r=*(progit);
      cout << *r;
    }

    //cout << (*edb).getArgument(1).getSring();
    for (AtomSet::const_iterator ai = edb->begin(); ai != edb->end(); ++ai) {
      cout << *ai << endl;
    }
    cout << "solve" << endl;
  #endif

  // 1. Art BaseASPSolver
  solver->solve(*idb, *edb, answersets);
  // 2. Art ASPFileSolver
  //solver.solve(*pp, *atsp, answersets);

  #ifdef DEBUG
    ResultContainer* result = new ResultContainer();
    for (std::vector<AtomSet>::const_iterator as = answersets.begin(); as!=answersets.end(); ++as) {
      result->addSet(*as);
    }

    OutputBuilder *outputbuilder = new TextOutputBuilder();
    result->print(std::cout, outputbuilder);

    cout << "-------------------------------------------" << endl;
  #endif

  if (answersets.size() > 0) {
    #ifdef DEBUG
      cout << "there are Answersets!!!! " << endl;
    #endif
    for (vector<AtomSet>::const_iterator as = answersets.begin(); as != answersets.end(); ++as) {
      for (AtomSet::const_iterator atsit = as->begin(); atsit != as->end(); ++atsit) {
        ret.insert(((*atsit).getArgument(0)).getString());
      }
    }
  }

  #ifdef DEBUG
    for (set<string>::iterator it = ret.begin(); it != ret.end(); ++it) {
      cout << "acc belief: " << *it << endl;
    }
  #endif

  return ret;
} // end ACC implementation*/
#endif

void
DLV_ASP_ContextAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {

  std::set<std::string> oset,aset,bset, aointerset, ominusaset;
  set<string> interset, accset;

  const std::string param = query.getInputTuple()[4].getUnquotedString();

  convertQueryToStringSets(query,aset,bset,oset);

//  cout << "param filename: " << param << endl;

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

  /////////////////////////////////////////////////////////////////
  //
  // Setting Up DLV Process and Options
  //
  /////////////////////////////////////////////////////////////////

  DLVProcess dlv;
  dlv.addOption("-facts");
  std::vector<AtomSet> answersets;
  std::vector<AtomSet>::const_iterator as;

  std::vector<std::string> tmp;

  //tmp.push_back(DLVPATH);
  // never include the set of initial facts in the answer sets
  tmp.push_back("-silent");


  /////////////////////////////////////////////////////////////////
  //
  // Setting Up Solver
  //
  /////////////////////////////////////////////////////////////////

  // 1. Art BaseASPSolver
  std::auto_ptr<BaseASPSolver> solver(dlv.createSolver());
  // 2. Art ASPFileSolver
  //std::auto_ptr<BaseASPSolver> solver(new ASPFileSolver<DLVresultParserDriver>(dlv,tmp));
    

  /*
  Program *idb = new Program();
  /// stores the facts of the program
  AtomSet *edb = new AtomSet();
  const Program *pp = idb;
  const AtomSet *atsp = edb;
  */


  /////////////////////////////////////////////////////////////////
  //
  // Parsing Programm
  //
  /////////////////////////////////////////////////////////////////

  //HexParserDriver driver;
  HexParserDriver driver;
  Program idb;
  /// stores the facts of the program
  AtomSet edb;
  driver.parse(param, idb, edb);

  //DLVresultParserDriver driver;
  //driver.parse(param, 


//  cout << "Atomset size: " << edb->size() << endl;
  // add Atomsets b<i>
  for (set<string>::iterator inputit = bset.begin(); inputit != bset.end(); ++inputit) {
    //*inputit
    #ifdef DEBUG
      cout << "added input belief: " << *inputit << endl;
    #endif
    edb.insert(AtomPtr(new Atom(Tuple(1, Term(*inputit)))));
  }
//  cout << "Atomset size: " << edb->size() << endl;

  // Rules of Programm
  RuleHead_t h;
  RuleBody_t b;
  h.clear();

  std::insert_iterator<std::set<std::string> > aointer_it(aointerset, aointerset.begin());
  set_intersection(aset.begin(), aset.end(), oset.begin(), oset.end(), aointer_it);

  for (set<string>::iterator interit = aointerset.begin(); interit != aointerset.end(); ++interit) {
    b.clear();
    b.insert(new Literal(AtomPtr(new Atom(*interit)), true));
    #ifdef DEBUG
      cout << "added inter Rule: :- not " << *interit << endl;
    #endif
    idb.addRule(new Rule(h,b));
  }

  std::insert_iterator<std::set<std::string> > ominusaset_it(ominusaset, ominusaset.begin());
  set_difference(oset.begin(), oset.end(), aset.begin(), aset.end(), ominusaset_it);

  for (set<string>::iterator aodiffit = ominusaset.begin(); aodiffit != ominusaset.end(); ++aodiffit) {
    b.clear();
    b.insert(new Literal(AtomPtr(new Atom(*aodiffit)), false));
    #ifdef DEBUG
      cout << "added diff set Rule: :- " << *aodiffit << endl;
    #endif
    idb.addRule(new Rule(h,b));
  }

  /////////////////////////////////////////////////////////////////
  //
  // Solve Program
  //
  /////////////////////////////////////////////////////////////////
  #ifdef DEBUG
    cout << "Start solving dlv program: " << endl;
    const Rule *r;
    int i=0;
    for (Program::const_iterator progit = idb.begin(); progit != idb.end(); ++i, ++progit) {
      r=*(progit);
      cout << *r;
    }

    //cout << (*edb).getArgument(1).getSring();
    for (AtomSet::const_iterator ai = edb.begin(); ai != edb.end(); ++ai) {
      cout << *ai << endl;
    }
    cout << "solve ==========================" << endl;
  #endif

  // 1. Art BaseASPSolver
  solver->solve(idb, edb, answersets);
  // 2. Art ASPFileSolver
  //solver.solve(*pp, *atsp, answersets);

  #if 0
    ResultContainer* result = new ResultContainer();

    for (as = answersets.begin(); as!=answersets.end(); ++as) {
      result->addSet(*as);
    }

    OutputBuilder *outputbuilder = new TextOutputBuilder();
    result->print(std::cout, outputbuilder);

    cout << "-------------------------------------------" << endl;
  #endif

  #ifdef DEBUG
    cout << "are there Answersets?????? " << endl;
    cout << "Answerset size: " << answersets.size() << endl;
  #endif

  if (answersets.size() > 0) {
    #ifdef DEBUG
      cout << "there are Answersets!!!! " << endl;
      cout  << "-------------------------------------------" <<  endl;
    #endif
    Tuple out;
    answer.addTuple(out);
  }
}

  } // namespace script
} // namespace dlvhex
