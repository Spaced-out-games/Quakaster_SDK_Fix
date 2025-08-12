#pragma once
#include "../Core.h"
#include <entt/entity/registry.hpp>


namespace qk {

	/// <summary>
	/// Represents an ECS context
	/// </summary>
	class QK_API Scene
	{
		entt::registry m_Registry;
		
	};
}
