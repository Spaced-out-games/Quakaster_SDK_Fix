#pragma once
#include "import.h"

namespace qk {
	// Initializes the graphics API
	void QK_API init_SDL_GL(int version_major, int version_minor);
	GLenum QK_API init_GLEW();

}

