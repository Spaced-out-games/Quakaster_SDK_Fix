#include "GameLayer.h"

namespace qk
{
	GameLayer::GameLayer(Scene& scene) : m_Scene(scene)
	{

	}

	void GameLayer::on_event(const SDL_Event& evt)
	{
		switch (evt.type)
		{
		case SDL_MOUSEBUTTONDOWN:

		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
			return ImGui::IsAnyItemActive() && io.WantCaptureMouse;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
		case SDL_TEXTINPUT:
			return ImGui::IsAnyItemActive() && io.WantCaptureKeyboard;

		default:
			return false;
		}
	}

	bool GameLayer::on_attach()
	{

	}

	void GameLayer::on_detach()
	{

	}

	void GameLayer::render()
	{

	}
}