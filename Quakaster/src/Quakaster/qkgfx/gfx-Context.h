#pragma once
#include "../Core.h"
#include "../qk/QKTL.h"
#include <SDL.h>
#include <GL/glew.h>
#include "Window.h"

namespace qk::gfx
{


	struct QK_API Context
	{
		SDL_GLContext m_Handle;
		Error init(Window& win);
		void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
		void swap(Window& win);
		void destroy();
		operator SDL_GLContext() { return m_Handle; }
	};


}
