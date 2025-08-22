#pragma once
#include "../Core.h"
#include <entt/entity/registry.hpp>


namespace qk {

	/// <summary>
	/// Represents an ECS context
	/// </summary>
    class QK_API Scene
    {
        friend class Entity;
        friend class AActor;

        entt::registry m_Registry;

    public:

        // Implicit cast to entt::registry&
        operator entt::registry& ();
        operator const entt::registry& () const;
    };
}
