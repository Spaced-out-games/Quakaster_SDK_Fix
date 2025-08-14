#include "CController.h"

namespace qk
{
	CController::CController() : m_Callback(nullptr) {}
	CController::CController(func_ptr_t<void, const SDL_Event&, entt::entity, qk::Scene&> callback) : m_Callback(callback)
	{

	}

	void CController::operator() (const SDL_Event& evt, entt::entity ent, qk::Scene& scene)
	{
		if (m_Callback) m_Callback(evt, ent, scene);
	}
}