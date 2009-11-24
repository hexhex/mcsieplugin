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
#include "dlvhex/ProgramCtx.h"
#include "dlvhex/DLVProcess.h"
#include "dlvhex/AtomSet.h"
#include "dlvhex/Program.h"
#include "dlvhex/ResultContainer.h"

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
/*
void
DLV_ASP_Context::retrieve(const Query& query, Answer& answer) throw (PluginError) {
  ProgramCtx pctx;
  std::set<std::string> oset,aset,bset;
  set<string> interset, accset;

  std::string param = query.getInputTuple()[4].getUnquotedString();
  convertQueryToStringSets(query,aset,bset,oset);
  cout << "param filename: " << param << endl;
  pctx.setProcess(new DLVProcess);
  //pctx.addInputSource(param);

  Tuple out;
  answer.addTuple(out);
}
*/


void
DLV_ASP_Context::retrieve(const Query& query, Answer& answer) throw (PluginError) {
//  ProgramCtx dlvpctx;
  std::set<std::string> oset,aset,bset;
  set<string> interset, accset;

  std::string param = query.getInputTuple()[4].getUnquotedString();
  convertQueryToStringSets(query,aset,bset,oset);
  cout << "param filename: " << param << endl;
 /* dlvpctx.setProcess(new DLVProcess);
  dlvpctx.addInputSource(param);
  dlvpctx.optimize();
  dlvpctx.safetyCheck();
  dlvpctx.strongSafetyCheck();
  dlvpctx.evaluate();
  dlvpctx.postProcess();
  dlvpctx.output();

  ResultContainer *rc = dlvpctx.getResultContainer();
  const ResultContainer::result_t& res = (*rc).getAnswerSets();
  if (res.empty())
    cout << "No Results" << endl;
*/

  Tuple out;
  answer.addTuple(out);
}

  } // namespace script
} // namespace dlvhex
