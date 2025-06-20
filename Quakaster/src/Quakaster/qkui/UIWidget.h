#pragma once
#include "../qkg/GL/import.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"


namespace qkui
{
	class UIContext;

	class QK_API UIWidget
	{
		public:
			UIWidget();
			virtual ~UIWidget();
			virtual void draw(UIContext& owner) = 0;
	};
}