#pragma once
#include <Quakaster/qk/Layer.h>



// Ends the application when the ESC key is pressed
struct GameLayer : qk::Layer
{
	~GameLayer();
	GameLayer();
	bool on_event(const SDL_Event& evt) override;
	void on_attach() override;
	void on_detach() override;
	void render() override;
};