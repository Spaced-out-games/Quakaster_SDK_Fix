#include "Scene.h"

namespace qk
{
	Scene::operator entt::registry& () { return m_Registry; }
	Scene::operator const entt::registry& () const { return m_Registry; }
}