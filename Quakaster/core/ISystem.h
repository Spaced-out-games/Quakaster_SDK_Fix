#pragma once
#include "../thirdparty/entt/src/entt/entity/registry.hpp"


namespace qk {
	using ISystem = void(*)(entt::registry&);
}