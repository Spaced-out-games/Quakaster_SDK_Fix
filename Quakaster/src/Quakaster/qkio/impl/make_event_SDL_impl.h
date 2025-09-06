#pragma once
#include "../Event.h"
#include "make_keycode_SDL_impl.h"
#include <SDL.h>

namespace qk::io
{
	template <>
	inline Event make_event<SDL_Event>(const SDL_Event& evt) noexcept
	{
		Event result;
		switch (evt.type)
		{
			case SDL_KEYDOWN:
				result.header.category = EEventCategory::KEY_EVENT;
				result.header.type.key_event = EKeyEvent::KEY_PRESS;
				result.header.variant = (uint16_t)make_keycode(evt.key.keysym.sym);
				result.payload.key_event.keycode = (int)evt.key.keysym.sym;
				result.payload.key_event.modifiers = evt.key.keysym.mod;
				result.payload.key_event.repeat = evt.key.repeat != 0;
				break;
			case SDL_KEYUP:
				result.header.category = EEventCategory::KEY_EVENT;
				result.header.type.key_event = EKeyEvent::KEY_RELEASE;
				result.header.variant = (uint16_t)make_keycode(evt.key.keysym.sym);
				result.payload.key_event.keycode = (int)evt.key.keysym.sym;
				result.payload.key_event.modifiers = evt.key.keysym.mod;
				result.payload.key_event.repeat = false;
				break;
			case SDL_MOUSEMOTION:
				result.header.category = EEventCategory::MOUSE_MOVE_EVENT;
				result.header.type.mouse_move_event = EMouseMoveEvent::MOUSE_MOVE;
				result.header.variant = 0;
				result.payload.mouse_move_event.delta_pos = { evt.motion.xrel, evt.motion.yrel };
				break;
			case SDL_MOUSEBUTTONDOWN:
				result.header.category = EEventCategory::MOUSE_EVENT;
				result.header.type.mouse_event = EMouseEvent::MOUSE_BUTTON_PRESS;
				result.header.variant = 0;
				result.payload.mouse_event.mouse_pos = { evt.button.x, evt.button.y };
				result.payload.mouse_event.clicks = evt.button.clicks;
				result.payload.mouse_event.button = evt.button.button;
				break;
			case SDL_MOUSEBUTTONUP:
				result.header.category = EEventCategory::MOUSE_EVENT;
				result.header.type.mouse_event = EMouseEvent::MOUSE_BUTTON_RELEASE;
				result.header.variant = 0;
				result.payload.mouse_event.mouse_pos = { evt.button.x, evt.button.y };
				result.payload.mouse_event.clicks = evt.button.clicks;
				result.payload.mouse_event.button = evt.button.button;
				break;
				
		default:
			break;
		}
		return result;
	}
}