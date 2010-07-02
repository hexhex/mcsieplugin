/* dlvhex-mcs-equilibrium-plugin
 * Calculate Equilibrium Semantics of Multi Context Systems in dlvhex
 *
 * Copyright (C) 2009,2010  Markus Boegl
 * 
 * This file is part of dlvhex-mcs-equilibrium-plugin.
 *
 * dlvhex-mcs-equilibrium-plugin is free software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * dlvhex-mcs-equilibrium-plugin is distributed in the hope that it will
 *  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dlvhex-dlplugin; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


/**
 * @file   DLV_ASP_ContextAtom.cpp
 * @author Markus Boegl
 * @date   Sun Jan 24 13:38:47 2010
 * 
 * @brief  Context to use ASP Programs
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "DLV_ASP_ContextAtom.h"
#include "Timing.h"

#include "dlvhex/DLVProcess.h"
#include "dlvhex/AtomSet.h"
#include "dlvhex/Program.h"
#include "dlvhex/HexParserDriver.h"
#include "dlvhex/ASPSolver.h"
#include "dlvhex/TextOutputBuilder.h"

#include <boost/foreach.hpp>

namespace dlvhex {
  namespace mcsdiagexpl {

using namespace std;

void printSet (std::string s) {
  std::cout << s << std::endl;
}

void
DLV_ASP_ContextAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
  const std::string& input = query.getInputTuple()[0].getString();
  const std::string& output = query.getInputTuple()[1].getString();
  const std::string& param = query.getInputTuple()[2].getUnquotedString();

	//std::cerr << "querying atom " << input << " " << output << " " << param << std::endl;

	// get bset from input
  std::set<std::string> bset;
	{
		AtomSet bset_a;
		query.getInterpretation().matchPredicate(input,bset_a);
		for(AtomSet::const_iterator at = bset_a.begin();
				at != bset_a.end(); ++at)
		{
			const std::string& inp = at->getArgument(1).getString();
			//std::cerr << "got inp " << inp << std::endl;
			bset.insert(inp);
		}
	}

	// get oset from output
  std::set<std::string> oset;
	{
		AtomSet oset_a;
		query.getInterpretation().matchPredicate(output,oset_a);
		for(AtomSet::const_iterator at = oset_a.begin();
				at != oset_a.end(); ++at)
		{
			const std::string& out = at->getArgument(1).getString();
			//std::cerr << "got out " << out << std::endl;
			oset.insert(out);
		}
	}

  #ifdef DEBUG
       std::cout << "===========================================" << std::endl;
       std::cout << param << std::endl;
       std::cout << "aset: " << std::endl;
       for_each(aset.begin(),aset.end(),printSet);
       std::cout << "oset: " << std::endl;
       for_each(oset.begin(),oset.end(),printSet);
       std::cout << "--------------------------------------------" << std::endl;
  #endif

  if((Timing::getInstance())->isActive()) {
	(Timing::getInstance())->start(context_id);
  }

  /////////////////////////////////////////////////////////////////
  //
  // Setting Up DLV Process and Options
  //
  /////////////////////////////////////////////////////////////////

  DLVProcess dlv;
  dlv.addOption("-facts");
	{
		std::ostringstream filter;
		filter << "-pfilter=";
		for(std::set<std::string>::const_iterator it = oset.begin();
				it != oset.end(); ++it)
		{
			if( it != oset.begin() )
				filter << ",";
			filter << *it;
		}
		//std::cerr << "adding option " << filter.str() << std::endl;
		dlv.addOption(filter.str());
	}
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

	#if 0
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
	#endif

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

  if((Timing::getInstance())->isActive()) {
	(Timing::getInstance())->stop(context_id);
  }

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

 // normalize answer sets (eliminate duplicates, as we filter some predicates and
 // thus have projected answer sets)
 std::set<std::set<std::string> > unique_answersets;
 for(as = answersets.begin(); as!=answersets.end(); ++as)
 {
	 std::set<std::string> this_answerset;
	 for(AtomSet::const_iterator atom = as->begin();
			 atom != as->end(); ++atom)
	 {
		 assert(atom->getArity() == 0 ); // must be propositional!
		 this_answerset.insert(atom->getPredicate().getString());
	 }
	 unique_answersets.insert(this_answerset);
 }

 unsigned asidx = 0; // handle counter
 BOOST_FOREACH(const std::set<std::string>& uas, unique_answersets)
 {
   Tuple basetuple;
	 // first output = handle
	 basetuple.push_back(Term(asidx));

	 if( uas.empty() )
	 {
		 // add a dummy belief (if there is no output belief, there can be no tuple otherwise)
   	 Tuple out(basetuple);
		 out.push_back(Term(0));
   	 answer.addTuple(out);
	 }
	 else
	 {
		 BOOST_FOREACH(const std::string& s, uas)
		 {
			 Tuple out(basetuple);
			 // second output = belief (here we only get filtered beliefs)
			 out.push_back(Term(s));
			 answer.addTuple(out);
		 }
	 }
	 asidx++;
 }
}

  } // namespace mcsdiagexpl
} // namespace dlvhex
