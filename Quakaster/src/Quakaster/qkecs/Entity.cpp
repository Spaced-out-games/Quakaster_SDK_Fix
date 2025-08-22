#include "Entity.h"
#include <entt/entity/fwd.hpp>

namespace qk
{
    Entity::Entity(entt::registry& registry)
        : m_Registry(registry), m_ID(m_Registry.create())
    {
        //from here, the Entity must be valid
    }

    Entity::Entity(entt::registry& registry, entt::entity id)
        : m_Registry(registry)
    {
        // we probably shouldn't trust that the ID is valid, so check that it even exists
        if (!m_Registry.valid(id))
        {
            m_ID = entt::null;
        }
        else
        {
            m_ID = id;
        }
    }

    inline void Entity::destroy() {
        if (valid()) {
            m_Registry.destroy(m_ID);
            m_ID = entt::null;
        }
    }

    inline bool Entity::valid() const {
        return m_ID != entt::null;
    }

}