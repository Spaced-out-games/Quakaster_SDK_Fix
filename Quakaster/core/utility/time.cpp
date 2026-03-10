#include "time.h"
#include <chrono>

namespace qk {
	uint64_t now() {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch())
			.count();
	}
}