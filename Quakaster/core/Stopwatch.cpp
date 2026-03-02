#include "Stopwatch.h"


namespace qk {

	uint64_t now() {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch())
			.count();
	}

	void Stopwatch::start() {
		m_StartTime = now();
	}
	void Stopwatch::stop() {
		if (m_StartTime == 0) return;
		m_TotalTime += now() - m_StartTime;
		m_StartTime = 0;
	}
	void Stopwatch::reset() {
		m_TotalTime = 0;
		m_StartTime = 0;
	}

	uint64_t Stopwatch::total_time() const { return m_TotalTime; }
	double Stopwatch::total_time_ms() const { return m_TotalTime / 1e6; }
	double Stopwatch::total_time_s() const { return m_TotalTime / 1e9; }

	ScopeTimer::~ScopeTimer() {
		if (m_Target) (*m_Target += (now() - m_StartTime));
	}

	ScopeTimer& ScopeTimer::operator=(ScopeTimer&& other) noexcept {
		if (this != &other) {
			// finalize current timer before overwriting
			if (m_Target) {
				*m_Target += (now() - m_StartTime);
			}

			m_Target = other.m_Target;
			m_StartTime = other.m_StartTime;

			other.m_Target = nullptr;
		}
		return *this;
	}

}