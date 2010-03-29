#ifndef _DLVHEX_MCSDIAGEXPL_TIMING_H_
#define _DLVHEX_MCSDIAGEXPL_TIMING_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <ostream>

namespace dlvhex {
  namespace mcsdiagexpl {

	using namespace boost::posix_time;
	using namespace boost::gregorian;

    class Timing {

      public:
	//Timing() : started(false), acc_count(0), null_duration(0,0,0) {};
	Timing();
	~Timing();
	static Timing* getInstance();
	bool begin();
	bool start();
	bool stop();
	bool end();
	int getAccCount() const { return acc_count; };
	time_duration getAvgAccDuration() const;
	time_duration getFullAccDuration() const;
	time_duration getFullPrgDuration() const;

      private:
	static Timing *t;
	bool started;
        ptime prg_start, prg_end;
        ptime acc_start;
        int acc_count;
        time_duration full_acc_duration, null_duration;
    }; // END class Timing


    static std::ostream&
    operator<< (std::ostream& out, const Timing& t){
	out << " -------------------------------------------------------------------------------------- " << std::endl;
    	out << "| time/call summary of Diagnosis and Explanation calculation for Multi Context Systems |" << std::endl;
	out << "| Program full duration " << t.getFullPrgDuration() << " | " << std::endl;
	out << "| Sum of all acc-function duration " << t.getFullAccDuration() << " | " << std::endl;
	out << "| Number of acc-function calls " << t.getAccCount() << " | " << std::endl;
	out << "| Average of acc-function duration " << t.getAvgAccDuration() << " | " << std::endl;
	out << " -------------------------------------------------------------------------------------- " << std::endl;
    	return out;
    };
    
  }  // END namespace mcsdiagexpl
} // END namespace dlvhex

#endif /*_DLVHEX_MCSDIAGEXPL_TIMING_H_*/
