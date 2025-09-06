#pragma once
#include <stdio.h>

namespace qk::io
{
	enum class EEventCategory : uint8_t
	{
		NULL_EVENT,
		MOUSE_EVENT,
		MOUSE_MOVE_EVENT,
		KEY_EVENT,
		KEY_REPEAT_EVENT,
		CLIENT_EVENT,
		SERVER_EVENT,
		APP_EVENT,
		WINDOW_EVENT,
		GAME_ACTION
	};
}