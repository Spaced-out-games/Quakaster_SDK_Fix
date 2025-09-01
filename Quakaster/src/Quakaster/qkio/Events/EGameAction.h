#pragma once
#include <stdint.h>


namespace qk::io
{
	enum class EGameAction : uint8_t
	{
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_FORWARD,
		MOVE_BACKWARD,
		CROUTCH,
		JUMP,
		WEAPON_FIRE,
		WEAPON_ALT_FIRE,
		WEAPON_RELOAD,
		WEAPON_SWITCH
	};
}