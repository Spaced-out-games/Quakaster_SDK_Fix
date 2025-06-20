#include "GameLayer.h"

GameLayer::~GameLayer()
{

}


GameLayer::GameLayer()
{

}

void GameLayer::on_attach()
{

}
bool GameLayer::on_event(const SDL_Event& evt)
{
	switch (evt.type)
	{
	case SDL_QUIT:
		qk::status = 1;
		return true;

	case SDL_KEYDOWN:
		if (evt.key.keysym.sym == SDLK_ESCAPE)
		{
			// Here, we'd invoke the console, but for now, just quit
			qk::status = 1;
			return true;
		}
		break;

	default:
		break;
	}
	return false; // Ensure every code path returns
}
void GameLayer::on_detach()
{

}

void GameLayer::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
}