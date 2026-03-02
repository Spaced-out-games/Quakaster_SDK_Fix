#pragma once
#include <entt/entity/registry.hpp>

namespace qk {
	using ISystem = void(*)(entt::registry&);
}