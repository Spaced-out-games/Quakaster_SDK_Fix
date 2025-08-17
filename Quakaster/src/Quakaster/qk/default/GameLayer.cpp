#include "GameLayer.h"

namespace qk
{
	GameLayer::GameLayer(Scene& scene) : m_Scene(scene)
	{

	}

	bool GameLayer::on_event(const SDL_Event& evt)
	{
		//auto view = m_Scene.registry().view<CController>
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
}