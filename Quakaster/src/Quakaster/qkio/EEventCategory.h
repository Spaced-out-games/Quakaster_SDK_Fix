#pragma once
#include "../Core.h"


namespace qk::io
{
	enum class EEventCategory : uint8_t
	{
		NULL_EVENT		= 0,
		// events relating to the app, window, system, engine...
		APP_EVENT		= BIT(0),

		// events relating to discrete inputs
		BUTTON_EVENT	= BIT(1),

		// events relating to continuous inputs
		AXIS_EVENT		= BIT(2),

		// events relating to the keyboard
		KEYBOARD_EVENT	= BIT(3),

		// events relating to the mouse
		MOUSE_EVENT		= BIT(4),

		// events relating to VR
		VR_EVENT		= BIT(5),

		// events relating to the game
		GAME_EVENT		= BIT(6),

		// Context-specific event category
		WILDCARD_EVENT	= BIT(7),
		
	};

	inline EEventCategory operator|(EEventCategory lhs, EEventCategory rhs)
	{
		return (EEventCategory)((uint8_t)lhs | (uint8_t)rhs);
	}

	inline bool operator&(EEventCategory lhs, EEventCategory rhs)
	{
		return (uint8_t)lhs & (uint8_t)rhs;
	}

	inline EEventCategory& operator|=(EEventCategory& lhs, EEventCategory rhs)
	{
		lhs = lhs | rhs;
		return lhs;
	}
	inline EEventCategory operator~(EEventCategory rhs)
	{
		return static_cast<EEventCategory>(~static_cast<uint8_t>(rhs));
	}



}