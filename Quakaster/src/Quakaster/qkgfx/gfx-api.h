#pragma once
#include "../Core.h"
#include "../qk/QKTL.h"
#include "gfx-window.h"

namespace qk::gfx
{

	struct Context_handle_t;

	struct QK_API Context
	{
		Context_handle_t* m_Handle;
		Error init(platform::Window& win);
		void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
		void swap(platform::Window& win);
		void destroy();
	};


}
