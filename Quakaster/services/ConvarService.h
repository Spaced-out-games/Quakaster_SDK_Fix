#pragma once
#include "../console/ConvarRegistry.h"
#include "../core/utility/Service.h"
#include "../core/utility/ScopeTimer.h"
#include "../core.h"

using namespace qk::console;


namespace qk::services {

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