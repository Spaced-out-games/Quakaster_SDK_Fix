#include "ControlLayer.h"

namespace qk
{
	GameLayer::GameLayer(Scene& scene) : m_Scene(scene)
	{

	}

	bool GameLayer::on_event(const SDL_Event& evt)
	{
		CGameEventFactory_SDL a;
		// find every entity with a game event queue and event factory
		auto view = m_Scene.view<CController, CGameEventQueue, CGameEventFactory_SDL>();
		
		for (entt::entity ent : view)
		{
			auto& game_event_factory = m_Scene.get<CGameEventFactory_SDL>(ent);
			auto& queue = m_Scene.get<CGameEventQueue>(ent);


			queue.push(game_event_factory(evt));

		}

		__debugbreak();
		return false;
	}

	void GameLayer::on_attach()
	{

	}

	void GameLayer::on_detach()
	{

	}

	void GameLayer::render()
	{

	}

	void SFlushGameEventQueue(Scene& scene)
	{
		auto view = scene.view<CController, CGameEventQueue>();

		for (entt::entity entity : view)
		{
			// call each controller, passing the queue game events
			auto& controller = scene.get<CController>(entity);
			auto& queue = scene.get<CGameEventQueue>(entity);

			while (!queue.empty()) {
				controller(queue.front(), entity, scene);
				queue.pop();
			}

		}

	}
}