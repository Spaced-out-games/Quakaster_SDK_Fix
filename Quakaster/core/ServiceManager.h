#pragma once
#include "../thirdparty/entt/src/entt/entity/registry.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include "IService.h"
#include "../core.h"

namespace qk {

	struct ServiceRef {
		IService* svc = nullptr;
		void (*dtor)(entt::registry*) = nullptr; // function pointer
		ServiceRef(IService* service, void (*destructor)(entt::registry*))
			: svc(service), dtor(destructor) {}
		ServiceRef() = default;
	};

	struct QK_API ServiceManager {
		std::unordered_map<std::string, ServiceRef> m_Services;
		entt::registry* registry = nullptr;

		template<class Service_t, class... Args>
		void add_service(const std::string& name, Args&&... args) {
			if (!registry) return;
			registry->ctx().emplace<Service_t>(std::forward<Args>(args)...);

			Service_t& svc = registry->ctx().get<Service_t>();

			m_Services[name] = ServiceRef{&svc, +[](entt::registry* registry) { registry->ctx().erase<Service_t>(); } // unary + converts to function ptr
			};

		}

		IService* get_service(const std::string& name);


		void remove_service(const std::string& name);

	};

} // namespace qk