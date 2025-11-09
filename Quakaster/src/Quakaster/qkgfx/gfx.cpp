#include "gfx.h"
#include <SDL.h>
#include <GL/glew.h> 


namespace qk::gfx
{
	Error init_SDL()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			return Error{ Error_t::PLATFORM_INIT_ERROR, SDL_GetError() };
		}
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // OpenGL 4.x
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); // for OpenGL 4.6
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return Error{ Error_t::NONE, nullptr };
	}

	Error init_GLEW()
	{
		GLenum err = glewInit();
		if (err != GLEW_OK) return { Error_t::GFX_API_LOADER_FAILURE, (const char*)glewGetErrorString(err) };
		return { Error_t::NONE, nullptr };

	}
}