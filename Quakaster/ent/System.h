#pragma once
#include <entt/entity/registry.hpp>
#include <vector>
#include "../core.h"

namespace qk::ent {

	using System_pfn_t = void(*)(entt::registry&);


	class QK_API System {
		System_pfn_t m_Implementation = nullptr;
		uint64_t	 m_TickInterval_ns = 0;
		uint64_t	 m_NextTick_ns = 0;
		public:
			void set_tick_interval_ns(uint64_t interval_ns);
			uint64_t get_tick_interval_ns();
			bool valid();
			bool ready();


			bool try_tick(entt::registry& registry);


	};



	using SystemStack = std::vector<System*>;

}