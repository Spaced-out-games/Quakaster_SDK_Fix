#pragma once
#include <Quakaster/qk/Layer.h>


struct LevelLayer : qk::Layer
{

	~LevelLayer();
	LevelLayer();
	bool on_event(const SDL_Event& evt) override;
	void on_attach() override;
	void on_detach() override;
	void render() override;
};