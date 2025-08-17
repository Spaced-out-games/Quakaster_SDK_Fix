#pragma once
#include <Quakaster/Core.h>
#include <Quakaster/qk/Layer.h>
#include <Quakaster/qkui/UIContext.h>
#include <Quakaster/qkecs/Scene.h>
#include <Quakaster/qkecs/components/CController.h>
#include <Quakaster/qkecs/components/CGameEventQueue.h>
#include <Quakaster/qkecs/components/CGameEventFactory.h>

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

	void SFlushGameEventQueue(Scene& scene);
}

