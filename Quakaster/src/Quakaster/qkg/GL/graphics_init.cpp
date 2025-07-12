#include "graphics_init.h"
#include <SDL.h>
#include "../../logging.h"
#include <stdexcept>

using namespace qk;

namespace qk {
	// Initializes SDL for OpenGL v. M.m
	void SDL_init_backend(int version_major, int version_minor, int version_patch)
	{
        int status = SDL_Init(SDL_INIT_VIDEO);
        if (status != 0)
        {
            //log("SDL Initialization failed: " + std::string(SDL_GetError()), LOG_ERROR_CRITICAL, CAT_GRAPHICS);
            throw std::runtime_error("SDL failed to initialize: " + std::string(SDL_GetError()));
        }


        log("SDL initialized successfully", LOG_INFO, CAT_GRAPHICS);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version_major);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, version_minor);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	}

    // updat this when you get a chance to use qk::Error
    void SDL_init_backend_symbol_loader()
    {
        SDL_GLContext currentContext = SDL_GL_GetCurrentContext();
        if (!currentContext) {
            __debugbreak();  // Or return false, depending on your policy
            throw std::runtime_error("[GLEW] No current OpenGL context\n");
        }

        glewExperimental = GL_TRUE;
        GLenum error = glewInit();
        if (error != GLEW_OK) {
            __debugbreak();  // Fatal error in debug mode
            throw std::runtime_error("[GLEW] failed to initialize" + std::string((const char*)glewGetErrorString(error)));
        }
    }

}