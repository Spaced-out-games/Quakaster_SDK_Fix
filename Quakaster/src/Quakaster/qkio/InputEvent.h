#pragma once
#include <stdint.h>
#include "../qkmath/vec2.h"
#include "../qkmath/vec3.h"


namespace qk
{
	enum class EInputEventType: uint16_t
	{
		NULL_EVENT,

		

		// mouse events
		MOUSE_EVENT = 0x0100,
		MOUSE_MOVE,
		MOUSE_STOP_MOVE,
		MOUSE_BUTTON_PRESS,
		MOUSE_BUTTON_RELEASE,
		MOUSE_BUTTON_REPEAT,

		// keyboard events
		KEY_EVENT = 0x0200,
		KEY_PRESS,
		KEY_RELEASE,
		KEY_REPEAT,

		INPUT_EVENT = 0x0300,

		// client events
		CL_EVENT = 0x0400,
		CL_CONNECT,
		CL_DISCONNECT,
		CL_TIMEOUT,
		CL_KICKED,
		CL_CRASHED,

		// server events
		SV_EVENT = 0x0800,
		SV_CONNECT,
		SV_DISCONNECT,
		SV_TIMEOUT,
		SV_CRASHED,

		NET_EVENT = 0x0c00,


		// application events
		APP_EVENT = 0x0f00,
		APP_BEGIN,
		APP_TICK,
		APP_END,
		APP_TERMINATING,
		APP_LOW_MEMORY,
		APP_OUT_OF_MEMORY,
		APP_BEFORE_ENTER_BACKGROUND,
		APP_AFTER_ENTER_BACKGROUND,
		APP_BEFORE_ENTER_FOREGROUND,
		APP_AFTER_ENTER_FOREGROUND,

		// Window events
		WIN_EVENT = 0x1000,
		WIN_SHOW,
		WIN_HIDE,
		WIN_EXPOSED,
		WIN_MOVED,
		WIN_BEFORE_RESIZE,
		WIN_AFTER_RESIZE,
		WIN_MINIMIZED,
		WIN_MAXIMIZED,
		WIN_RESTORED,
		WIN_MOUSE_ENTER,
		WIN_MOUSE_EXIT,
		WIN_KEYBOARD_FOCUS_GAINED,
		WIN_KEYBOARS_FOCUS_LOST,
		WIN_OPEN,
		WIN_CLOSED,

		ENGINE_EVENT = 0x1f00,


		// Physics events
		PHYS_EVENT = 0x2f00,
		PHYS_TICK,

	};

	struct MouseMoveEvent
	{
		// vec3s so that access patterns are consistent with other event types

		vec3 absolute;
		vec3 relative

	};

	struct MouseButtonEvent
	{
		uint8_t button;
		uint8_t clicks;
	};





}