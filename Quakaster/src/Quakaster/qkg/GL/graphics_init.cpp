#include "graphics_init.h"

using namespace qk;

namespace qk {
	// Initializes SDL for OpenGL v. M.m
	void init_SDL_GL(int version_major, int version_minor)
	{
		#ifdef _DEBUG
			log("Initializing SDL and OpenGL 3.3", LOG_INFO, CAT_GRAPHICS);
		#else // I swear to fucking god I hate the autoindent of #endif
		#endif


		SDL_Init(SDL_INIT_VIDEO);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version_major);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, version_minor);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


	}

	GLenum init_GLEW()
	{
		SDL_GLContext currentContext = SDL_GL_GetCurrentContext();
		if (currentContext == nullptr) {
			std::cerr << "No OpenGL context is current!\n";
		}
		else {
			std::cout << "[ENGINE] OpenGL context is current at: " << currentContext << "\n";
		}
		glewExperimental = GL_TRUE;
		auto a = glewInit();
		std::cout << "glGenBuffers: " << glGenBuffers << '\n';
		std::cout << "GLEW status: " << a << '\n';

		return a;
	}

}