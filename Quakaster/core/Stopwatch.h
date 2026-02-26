#pragma once
#include "../core.h"
#include <stdint.h>
#include <chrono>

namespace qk {

	QK_API uint64_t now();

	struct QK_API Stopwatch {
		uint64_t m_StartTime = 0;
		uint64_t m_TotalTime = 0;

		void start();

		void stop();

		void reset();

		[[nodiscard]] uint64_t total_time() const;

		[[nodiscard]] double total_time_ms() const;
		[[nodiscard]] double total_time_s() const;
	};

    struct QK_API ScopeTimer {
        Stopwatch& target;

        explicit ScopeTimer(Stopwatch& svc) : target(svc) {
            target.start();
        }

        ~ScopeTimer() {
            target.stop();
        }

        // non-copyable
        ScopeTimer(const ScopeTimer&) = delete;
        ScopeTimer& operator=(const ScopeTimer&) = delete;

        // movable if you need
        ScopeTimer(ScopeTimer&& other) noexcept : target(other.target) {}
        ScopeTimer& operator=(ScopeTimer&& other) noexcept { return *this; }
    };

}