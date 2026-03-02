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
        uint64_t* m_Target = nullptr;
        uint64_t m_StartTime = 0;

        explicit ScopeTimer(uint64_t* target_out) {
            m_Target = target_out;
            m_StartTime = now();
        }

        ~ScopeTimer();

        // non-copyable
        ScopeTimer(const ScopeTimer&) = delete;
        ScopeTimer& operator=(const ScopeTimer&) = delete;

        ScopeTimer(ScopeTimer&& other) noexcept : m_Target(other.m_Target), m_StartTime(other.m_StartTime) { other.m_Target = nullptr; }
        ScopeTimer& operator=(ScopeTimer&& other) noexcept;
    };

}