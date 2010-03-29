#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "Timing.h"

namespace dlvhex {
  namespace mcsdiagexpl {

	Timing* Timing::t = NULL;

	Timing::Timing() {
		acc_count = 0;
		started = false;
	}

	Timing::~Timing() {
		
	}

	Timing*
	Timing::getInstance() {
		if (t == NULL) {
		  t = new Timing();
		}
		return t;
	}

	bool
	Timing::begin() {
		std::cout << "Program Begin" << std::endl;
		if (!started) {
			std::cout << "Start time" << std::endl;
			prg_start = microsec_clock::local_time();
			started=true;
			std::cout << "Programm start time: " << prg_start << std::endl;
			return true;
		}
		return false;
	}

	bool
	Timing::start() {
		std::cout << "ACC STARTED" << std::endl;
		if (acc_count >= 0) {
			acc_count *= -1;
			acc_count -= 1;
			acc_start  = microsec_clock::local_time();
			return true;
		}
		return false;
	}

	bool
	Timing::stop() {
		std::cout << "ACC END" << std::endl;
		if (acc_count < 0) {
			acc_count *= -1;
			ptime now = microsec_clock::local_time();
			time_duration single_acc_duration = now - acc_start;
			full_acc_duration += single_acc_duration;
			return true;
		}
		return false;
	}

	bool
	Timing::end() {
		std::cout << "Program END" << std::endl;
		if (started) {
			prg_end = microsec_clock::local_time();
			std::cout << "Programm end time: " << prg_end << std::endl;
			if (prg_start < prg_end)
				return true;
		}
		return false;
	}

	time_duration 
	Timing::getAvgAccDuration() const {
		if ((acc_count > 0) && (full_acc_duration > null_duration))
			return full_acc_duration/acc_count;
		return null_duration;
	}

	time_duration 
	Timing::getFullAccDuration() const {
		if ((acc_count > 0) && (full_acc_duration > null_duration))
			return full_acc_duration;
		return null_duration;
	}

	time_duration
	Timing::getFullPrgDuration() const {
		time_duration full_prg_duration = prg_end - prg_start;
		if (full_prg_duration > null_duration)
			return full_prg_duration;
		return null_duration;
	}

 #if 0   
    void printBench(std::ostream& out){
	out << "----------------------------------------------------------------------------------------" << std::endl;
    	out << "| time/call summary of Diagnosis and Explanation calculation for Multi Context Systems |" << std::endl;
	out << "| Program full duration " << (Timing::getInstance())->getFullPrgDuration() << " | " << std::endl;
	//out << "| Sum of all acc-function duration " << t.getFullAccDuration << " | " << std::endl;
	//out << "| Number of acc-function calls " << t.getAccCount() << " | " << std::endl;
	//out << "| Average of acc-function duration " << t.getAvgAccDuration << " | " << std::endl;
	out << "----------------------------------------------------------------------------------------" << std::endl;
    }
#endif

  } // namespace script
} // namespace dlvhex
