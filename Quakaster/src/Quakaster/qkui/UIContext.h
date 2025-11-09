#pragma once
#include <GL/glew.h>
#include <SDL.h>
//#include "../qkg/GL/import.h"
#include "imgui.h"
#include "backends/imgui_impl_qkio-sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "UIWidget.h"




namespace qk::ui
{
	class UIWidget;

	class QK_API UIContext
	{
		private:
			SDL_Window* m_Target;
			uint8_t m_EmptyCount = 0;
			std::vector<UIWidget*> m_Widgets; // Might be worth making this an array instead?
		public:
			ImGuiContext* m_Context;
			UIContext();
			~UIContext();
			ImGuiIO& IO();

			// Legacy support
			inline void init(ImGuiContext* im_context, SDL_GLContext context, SDL_Window* window);

			// Begins an ImGui frame. Might be worth moving this into draw()
			inline void begin();

			// Draws all the ImGui widgets.
			inline void draw();

			// Renders out the ImGui widgets. Might be worth moving this into draw()
			inline void end();

			// Adds a widget to the UIContext.
			inline [[nodiscard]] uint8_t add_widget(UIWidget* widget);

			// Removes a widget from the UIContext.
			inline bool remove_widget(uint8_t handle);

	};
}