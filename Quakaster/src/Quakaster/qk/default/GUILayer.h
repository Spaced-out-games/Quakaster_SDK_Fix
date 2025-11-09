#pragma once
#include "../../Core.h"
#include "../Layer.h"
#include "../../qkui/UIContext.h"

namespace qk
{

	// Quakaster's default GUI layer. Displays ImGui widgets
	struct QK_API GUILayer : qk::Layer
	{
		// Pointer to the UIContext that holds this GUILayer
		qk::ui::UIContext* m_UIContext = nullptr;

		// Standard qk::Layer implementation for GUIs
		GUILayer(qk::ui::UIContext* UIContext);
		inline void init(SDL_GLContext& context, SDL_Window* window);
		bool on_event(const SDL_Event& evt) override;
		void on_attach() override;
		void on_detach() override;
		void render() override;
	};

}