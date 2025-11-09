#pragma once
#include "../Core.h"
#include <GL/glew.h>
#include "imgui.h"
#include "backends/imgui_impl_qkio-sdl2.h"
#include "backends/imgui_impl_opengl3.h"


namespace qk::ui
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