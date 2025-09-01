#pragma once
#include "Event.h"
#include <SDL.h>

namespace qk
{
	// Generates qkio events from an SDL_Event
	qk::io::Event qkioEvent_SDL2_impl(const SDL_Event& event);
}