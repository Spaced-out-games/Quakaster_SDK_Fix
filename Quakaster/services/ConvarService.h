/// **************************************** QUAKASTER ENGINE **************************************** 
/// services/ConvarService.h
/// Purpose: Provides a service to add, remove, and modify console variables by name.
/// **************************************************************************************************

#pragma once
#include "../CLI/ConvarRegistry.h"
#include "../core/utility/Service.h"
#include "../core/utility/ScopeTimer.h"
#include "../core.h"

using namespace qk::CLI;


namespace qk::svc {

	class QK_API ConvarService: util::IService{


		ConvarRegistry m_Registry;

		public:
			bool has(const std::string& id);
			bool set(const std::string& id, convar_t new_value);
			template <class T>
			T* try_get(const std::string& id) {
				util::ScopeTimer timer(uptime_ptr());
				return m_Registry.try_get<T>(id);
			}
	};

}