#ifndef TIMING_H_
#define TIMING_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <ostream>

namespace dlvhex {
  namespace diagexpl {

	using namespace boost::posix_time;
	using namespace boost::gregorian;

    class Timing {

      public:
	//Timing() : started(false), acc_count(0), null_duration(0,0,0) {};
	Timing() {};
	bool begin();
	bool start();
	bool stop();
	bool end();
	int getAccCount() { return acc_count; };
	time_duration getAvgAccDuration();
	time_duration getFullAccDuration();
	time_duration getFullPrgDuration();

      private:
	bool started;
        ptime prg_start, prg_end;
        ptime acc_start;
        int acc_count;
        time_duration full_acc_duration, null_duration;
    }; // END class Timing
    
    static std::ostream&
    operator<< (std::ostream& out, const Timing& t){
    	out << "time/call summary of Diagnosis and Explanation calculation for Multi Context Systems" << std::endl;
    	return out;
    };
    
  }  // END namespace diagexpl
} // END namespace dlvhex

#endif /*TIMING_H_*/
