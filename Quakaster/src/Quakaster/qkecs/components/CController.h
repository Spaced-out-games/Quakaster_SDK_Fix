#pragma once
#include "../../Core.h"
#include "../../qk/QKTL.h"
#include <SDL_events.h>
#include <entt/entity/entity.hpp>
#include "../Scene.h"


namespace qk
{
	// Receives an SDL_Event, entt::entity and Scene& -> operates on the target entity
	struct QK_API CController
	{
		CController();
		CController(func_ptr_t<void, const SDL_Event&, entt::entity, qk::Scene&> callback);
		func_ptr_t<void, const SDL_Event&, entt::entity, qk::Scene&> m_Callback;

		void operator()(const SDL_Event&, entt::entity, qk::Scene&);
	};
}