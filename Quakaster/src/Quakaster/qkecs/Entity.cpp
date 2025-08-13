#include "Entity.h"
#include <entt/entity/fwd.hpp>

namespace qk
{
	void Entity::destroy(Scene& scene)
	{
		scene.m_Registry.destroy(m_ID);
		m_ID = entt::null;
	}

	Entity::Entity()
	{
		m_ID = entt::null;
	}

	Entity::Entity(Scene& scene)
	{
		m_ID = scene.m_Registry.create();
	}
}