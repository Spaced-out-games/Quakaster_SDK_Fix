#pragma once
#include "../../Core.h" // for QK_API
#include "../Layer.h"
#include "GL/glew.h"


namespace qk
{
	// The base Quakaster input layer. Exits the application when ESC is pressed.
	struct QK_API QKBaseLayer : qk::Layer
	{
		~QKBaseLayer();

		// Standard qk::Layer implementation for receiving input that other layers don't.
		QKBaseLayer();
		bool on_event(const SDL_Event& evt) override;
		void on_attach() override;
		void on_detach() override;
		void render() override;
	};
}