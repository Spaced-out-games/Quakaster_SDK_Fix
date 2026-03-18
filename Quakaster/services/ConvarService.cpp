#include "ConvarService.h"


namespace qk::svc {
	bool ConvarService::has(const std::string& id) {
		util::ScopeTimer timer(uptime_ptr());
		return m_Registry.has(id);
	}
	bool ConvarService::set(const std::string& id, convar_t new_value) {
		util::ScopeTimer timer(uptime_ptr());
		return m_Registry.set(id, new_value);
	}

}