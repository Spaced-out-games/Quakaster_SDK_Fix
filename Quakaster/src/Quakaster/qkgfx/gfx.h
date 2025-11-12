#pragma once
#include "../Core.h"
#include "Error.h"

// Declares a platform-agnostic API for creating a platform context
namespace qk::gfx
{
	// Initializes SDL
	qk::gfx::Result QK_API init_SDL();
	qk::gfx::Result QK_API init_GLEW();
}