#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

//#define DEBUG

#include "Timing.h"

namespace dlvhex {
  namespace mcsdiagexpl {

	Timing::Timing() {
		started = false;
		activated = false;
	}

	Timing&
	Timing::getInstance() {
		static Timing t;
		return t;
	}

	void 
	Timing::activate() {
	  activated = true;
	}

	bool
	Timing::isActive() {
	  return activated;
	}

	bool
	Timing::begin() {
		if (!started) {
			prg_start = microsec_clock::local_time();
			started=true;
			#ifdef DEBUG
			  std::cout << "PROGRAM BEGIN TIME: " << prg_start << std::endl;
			#endif
			return true;
		}
		return false;
	}

	bool
	Timing::start(int id) {	
		acc_time_info curr = acc_info_map[id];
		#ifdef DEBUG
		  std::cout << "ACC START ID: " << id << std::endl;
		  std::cout << "CURR Count: " << curr.count << std::endl;
		#endif
		if (curr.count >= 0) {
			curr.count *= -1;
			curr.count -= 1;
			curr.start  = microsec_clock::local_time();
			acc_info_map[id] = curr;
			return true;
		}
		return false;
	}

	bool
	Timing::stop(int id) {
		acc_time_info curr = acc_info_map[id];
		#ifdef DEBUG
		  std::cout << "ACC END ID: " << id << std::endl;
		  std::cout << "CURR Count: " << curr.count << std::endl;
		#endif
		if (curr.count < 0) {
			curr.count *= -1;
			ptime now = microsec_clock::local_time();
			time_duration single_acc_duration = now - curr.start;
			curr.duration += single_acc_duration;
			acc_info_map[id] = curr;
			return true;
		}
		return false;
	}

	bool
	Timing::end() {
		if (started) {
			prg_end = microsec_clock::local_time();
			#ifdef DEBUG
			  std::cout << "PROGRAM END TIME: " << prg_end << std::endl;
			#endif
			if (prg_start < prg_end)
				return true;
		}
		return false;
	}

	time_duration
	Timing::getFullPrgDuration() const {
		time_duration full_prg_duration = prg_end - prg_start;
		if (full_prg_duration > null_duration)
			return full_prg_duration;
		return null_duration;
	}

	std::ostream& 
	Timing::getAccOutput(std::ostream& out) const {
		//std::ostream& out;
		std::string dString;
		time_duration full_all_acc_duration = time_duration(0,0,0);
		//for loop in contexts
		for (std::map<int, acc_time_info>::const_iterator it = acc_info_map.begin(); it != acc_info_map.end(); it++) {
			acc_time_info curr = (*it).second;
			//write Context ID
			out << "| ";
			std::stringstream sscid;
			sscid << (*it).first;
			std::string cid = sscid.str();
			out << cid;
			for (int i = cid.size(); i<14; out << " ", i++);
			out << " | ";

			full_all_acc_duration += curr.duration;
			//Total Time in ACC Function
			if ((curr.count > 0) && (curr.duration > null_duration)) {
				dString = boost::posix_time::to_simple_string(curr.duration);
			} else {
				dString = boost::posix_time::to_simple_string(null_duration);
			}
			out << dString;
			for (int i = dString.size(); i<15; out << " ", i++);
			out << " | ";

			// Average acc function duration
			if ((curr.count > 0) && (curr.duration > null_duration)) {
				dString = boost::posix_time::to_simple_string(curr.duration/curr.count);
			} else {
				dString = boost::posix_time::to_simple_string(null_duration);
			}
			out << dString;
			for (int i = dString.size(); i<15; out << " ", i++);
			out << " | ";
	
			// Number of acc fuction calls
			std::stringstream accCount;
			accCount << curr.count;
			std::string accCountS = accCount.str();	
			for (int i = accCountS.size(); i<14; out << " ", i++);
			out << accCountS;
			out << " |" << std::endl;

		} //end loop

		out << " ===================================================================== " << std::endl;
		out << "| Total time for all ACC Functions | Total time for Program           |" << std::endl;
		out << "|----------------------------------|----------------------------------|" << std::endl;
		out << "| ";
		dString = boost::posix_time::to_simple_string(full_all_acc_duration);
		out << dString;
		for (int i = dString.size(); i<15; out << " ", i++);
		out << "                  | ";

		return out;
	}

  } // namespace script
} // namespace dlvhex
