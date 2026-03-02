#pragma once
#include <entt/entity/registry.hpp>
#include <vector>

namespace qk {
	using ISystem = void(*)(entt::registry&);

	using SystemStack = std::vector<ISystem*>;

}