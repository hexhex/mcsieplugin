#include "ContextAtom.h"
#include "ContextPlugin.h"

DLVHEX_MCSEQUILIBRIUM_PLUGIN(BenchmarkPlugin8,0,1,0)

namespace
{
  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext1,"benchcontext8_context_acc1")

  std::set<std::set<std::string> > BenchContext1::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    if (input.find("a") != input.end()) {
	s.insert("a");
    }
    if (input.find("b") != input.end()) {
	s.insert("b");
    }
    if ((input.find("a") != input.end()) || (input.find("b") != input.end())) {
	ret.insert(s);
    }
    if ((input.find("a") == input.end()) && (input.find("b") == input.end())) {
	s.insert("a");
	ret.insert(s);
	s.clear();
	s.insert("b");
	ret.insert(s);
    }
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext2,"benchcontext8_context_acc2")

  std::set<std::set<std::string> > BenchContext2::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    if (input.find("a") != input.end()) {
	s.insert("a");
    }
    if (input.find("b") != input.end()) {
	s.insert("b");
    }
    ret.insert(s);
    if ((input.find("a") == input.end()) && (input.find("b") == input.end())) {
	s.insert("a");
	ret.insert(s);
	s.clear();
	s.insert("b");
	ret.insert(s);
    }
    return ret;
  }

  DLVHEX_MCSEQUILIBRIUM_CONTEXT(BenchContext3,"benchcontext8_context_acc3")

  std::set<std::set<std::string> > BenchContext3::acc(const std::string& param, const std::set<std::string>& input) {
    std::set<std::set<std::string> > ret;
    std::set<std::string> s;
    if (input.find("a") != input.end()) {
	s.insert("a");
    }
    if (input.find("b") != input.end()) {
	s.insert("b");
    }
    ret.insert(s);
    if ((input.find("a") == input.end()) && (input.find("b") == input.end())) {
	s.insert("a");
	ret.insert(s);
	s.clear();
	s.insert("b");
	ret.insert(s);
    }
    return ret;
  }

  void BenchmarkPlugin8::registerAtoms() {
    registerAtom<BenchContext1>();
    registerAtom<BenchContext2>();
    registerAtom<BenchContext3>();
  }
}
