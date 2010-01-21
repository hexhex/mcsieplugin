#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

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

void printSet (std::string s) {
  std::cout << s << std::endl;
}

void
DLV_ASP_ContextAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
  std::set<std::string> oset,aset,bset, aointerset, ominusaset;
  set<string> interset, accset;

  const std::string param = query.getInputTuple()[4].getUnquotedString();

  convertQueryToStringSets(query,aset,bset,oset);

  #ifdef DEBUG
       std::cout << "===========================================" << std::endl;
       std::cout << param << std::endl;
       std::cout << "aset: " << std::endl;
       for_each(aset.begin(),aset.end(),printSet);
       std::cout << "oset: " << std::endl;
       for_each(oset.begin(),oset.end(),printSet);
       std::cout << "--------------------------------------------" << std::endl;
  #endif

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

  /////////////////////////////////////////////////////////////////
  //
  // Parsing Programm given as param into idb and edb
  //
  /////////////////////////////////////////////////////////////////

  //HexParserDriver driver;
  HexParserDriver driver;
  Program idb;
  /// stores the facts of the program
  AtomSet edb;
  driver.parse(param, idb, edb);

  /////////////////////////////////////////////////////////////////
  //
  // add additional rules to the program
  //
  /////////////////////////////////////////////////////////////////

  // add Atomsets b<i> as facts to program
  for (set<string>::iterator inputit = bset.begin(); inputit != bset.end(); ++inputit) {
    //*inputit
    #ifdef DEBUG
      cout << "added input belief: " << *inputit << endl;
    #endif
    edb.insert(AtomPtr(new Atom(Tuple(1, Term(*inputit)))));
  }

  // Rules of Programm
  RuleHead_t h;
  RuleBody_t b;
  h.clear();

  // add the intersection of A and O as Constraint ":- not x."
  std::insert_iterator<std::set<std::string> > aointer_it(aointerset, aointerset.begin());
  set_intersection(aset.begin(), aset.end(), oset.begin(), oset.end(), aointer_it);
  for (set<string>::iterator interit = aointerset.begin(); interit != aointerset.end(); ++interit) {
    b.clear();
    b.insert(new Literal(AtomPtr(new Atom(*interit)), true));
    #ifdef DEBUG
      cout << "added inter Rule: :- not " << *interit << endl;
    #endif
    Rule *r = new Rule(h,b);
    idb.addRule(r);
  }

  // add the difference of O and A as Constraint ":- x."
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

  #ifdef DEBUG
       ResultContainer* result = new ResultContainer();
   
       for (as = answersets.begin(); as!=answersets.end(); ++as) {
         result->addSet(*as);
       }
   
       OutputBuilder *outputbuilder = new TextOutputBuilder();
       result->print(std::cout, outputbuilder);
   
       cout << "-------------------------------------------" << endl;

       cout << "are there Answersets?????? " << endl;
       cout << "Answerset size: " << answersets.size() << endl;
  #endif


  if (answersets.size() > 0) {
    Tuple out;
    answer.addTuple(out);
  }
}

  } // namespace mcsequilibrium
} // namespace dlvhex
