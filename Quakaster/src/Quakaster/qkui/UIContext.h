#pragma once
#include "../qkg/GL/import.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "UIWidget.h"


namespace qkui
{
	class UIWidget;

	class QK_API UIContext
	{
		SDL_Window* m_Target;
		uint8_t m_EmptyCount = 0;
		std::vector<UIWidget*> m_Widgets;
		public:
			ImGuiContext* m_Context;
			UIContext();
			~UIContext();
			ImGuiIO& IO();
			inline void init(SDL_GLContext& context, SDL_Window* window);
			inline void begin();
			inline void draw();
			inline void end();

			inline [[nodiscard]] uint8_t add_widget(UIWidget* widget);
			inline bool remove_widget(uint8_t handle);

	};
}