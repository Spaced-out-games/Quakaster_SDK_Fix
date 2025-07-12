#pragma once
#include "../../Core.h"
#include <GL/glew.h>


namespace qk {
	// Initializes the backend (OpenGL, Vulkan, DirectX, etc)
	void QK_API SDL_init_backend(int version_major, int version_minor, int version_patch = 0);

	// Initializes the symbol loader
	void QK_API SDL_init_backend_symbol_loader();

}

