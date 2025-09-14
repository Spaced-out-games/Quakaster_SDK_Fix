#pragma once
#include <SDL.h>
#include "../KeyEvent.h"

namespace qk::io
{
	Event QK_API from_SDL_Event(const SDL_Event& evt);

}