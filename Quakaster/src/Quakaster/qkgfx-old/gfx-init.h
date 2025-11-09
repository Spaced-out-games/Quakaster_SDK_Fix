#pragma once
#include "../Core.h"
#include "gfx-core.h"

// Declares a platform-agnostic API for creating a platform context
namespace qk::gfx::platform
{
	// Initializes the platform.
	Error QK_API init();
}

namespace qk::gfx::loader
{
	Error QK_API load();
}