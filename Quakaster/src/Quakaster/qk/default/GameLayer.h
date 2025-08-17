#pragma once
//#include <Quakaster/Core.h>

#include "../../Core.h"
#include "../../qk/Layer.h"
#include "../../qkecs/Scene.h"

namespace qk
{
	struct GameLayer : qk::Layer
	{
		qk::Scene& m_Scene;

		GameLayer(qk::Scene& scene);

		bool on_event(const SDL_Event& evt) override;
		void on_attach() override;
		void on_detach() override;
		void render() override;
	};
}