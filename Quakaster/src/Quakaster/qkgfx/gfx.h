#pragma once
#include "../Core.h"
#include "Error.h"

// Declares a platform-agnostic API for creating a platform context
namespace qk::gfx
{
	// Initializes SDL
	Error QK_API init_SDL();
	Error QK_API init_GLEW();
}