#pragma once
#include <SDL.h>
#include "../KeyEvent.h"
#include "../QuitEvent.h"
#include "../MouseMoveEvent.h"
namespace qk::io
{
	Event QK_API from_SDL_Event(const SDL_Event& evt);

}