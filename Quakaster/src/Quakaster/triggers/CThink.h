#pragma once
#include "../Core.h"
#include "../qk/QKTL.h"
#include <entt/entity/entity.hpp>


// Ticking function component
struct QK_API CThink
{
	func_ptr_t<void, entt::registry&, entt::entity> m_Think = nullptr;
	void operator()(entt::registry& registry, entt::entity target);
};


