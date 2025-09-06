#pragma once
#include <stdint.h>


namespace qk::io
{
	enum class EMouseMoveEvent : uint8_t
	{
		MOUSE_MOVE
	};

	enum class EMouseEvent : uint8_t
	{

		MOUSE_STOP_MOVE,
		MOUSE_BUTTON_PRESS,
		MOUSE_BUTTON_RELEASE,
		MOUSE_BUTTON_REPEAT
	};
}