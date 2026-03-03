#pragma once
#include "ConvarRegistry.h"
#include "../core/IService.h"
#include "../core/Stopwatch.h"
#include "../core.h"


namespace qk::console {

	class QK_API ConvarService: IService {
		ConvarRegistry m_Registry;

		public:
			bool has(const std::string& id);
			bool set(const std::string& id, convar_t new_value);
			template <class T>
			T* try_get(const std::string& id) {
				ScopeTimer timer(uptime_ptr());
				return m_Registry.try_get<T>(id);
			}
	};

}