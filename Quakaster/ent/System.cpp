#include "System.h"
#include <time.h>
#include "../core/utility/time.h"

namespace qk::ent {
	void System::set_tick_interval_ns(uint64_t interval_ns) {
		m_TickInterval_ns = interval_ns;
	}

	uint64_t System::get_tick_interval_ns() {
		return m_TickInterval_ns;
	}

	bool System::valid() {
		return m_Implementation != nullptr;
	}

	bool System::ready() {
		return util::now() >= m_NextTick_ns;
	}



	bool System::try_tick(entt::registry& registry) {
		if (!m_Implementation) return false;
		if (!ready()) return false;
		m_NextTick_ns += m_TickInterval_ns;
		m_Implementation(registry);

		return true;

	}
}