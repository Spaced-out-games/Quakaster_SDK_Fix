#pragma once
#include <Quakaster/qk/Layer.h>
#include <Quakaster/qkui/UIContext.h>

//ImGui_ImplSDL2_ProcessEvent(&event)


struct GUILayer : qk::Layer
{
	//SDL_GLContext& context, SDL_Window* window
	qkui::UIContext* m_UIContext = nullptr;
	GUILayer(qkui::UIContext* UIContext);
	inline void init(SDL_GLContext& context, SDL_Window* window);
	bool on_event(const SDL_Event& evt) override;
	void on_attach() override;
	void on_detach() override;
	void render() override;
};