#include "CThink.h"

void CThink::operator()(entt::registry& registry, entt::entity target)
{
	if (m_Think)
	{
		m_Think(registry, target);
	}
}