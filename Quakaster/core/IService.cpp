#include "IService.h"
#include "spdlog/spdlog.h"

namespace qk {
	size_t IService::uptime_ns() { return m_Uptime_ns; }

	size_t* IService::uptime_ptr() { return &m_Uptime_ns; }


	void IService::init() {
		spdlog::info("Service initialized at {:#x}", (uintptr_t)this);

	}
	void IService::shutdown() {
		spdlog::info("Service shutdown at {:#x}", (uintptr_t)this);

	}

}