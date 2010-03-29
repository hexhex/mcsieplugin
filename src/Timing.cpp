#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "Timing.h"

namespace dlvhex {
  namespace diagexpl {

	bool
	Timing::begin() {
		if (!started) {
			prg_start = microsec_clock::local_time();
			return true;
		}
		return false;
	}

	bool
	Timing::start() {
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
		prg_end = microsec_clock::local_time();
		if (prg_start < prg_end)
			return true;
		return false;
	}

	time_duration 
	Timing::getAvgAccDuration() {
		if ((acc_count > 0) && (full_acc_duration > null_duration))
			return full_acc_duration/acc_count;
		return null_duration;
	}

	time_duration 
	Timing::getFullAccDuration() {
		if ((acc_count > 0) && (full_acc_duration > null_duration))
			return full_acc_duration;
		return null_duration;
	}

	time_duration
	Timing::getFullPrgDuration() {
		time_duration full_prg_duration = prg_end - prg_start;
		if (full_prg_duration > null_duration)
			return full_prg_duration;
		return null_duration;
	}

  } // namespace script
} // namespace dlvhex
