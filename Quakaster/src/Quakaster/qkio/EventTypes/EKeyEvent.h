#pragma once
#include <stdint.h>

namespace qk::io
{
	

	enum class EKeyRepeatEvent: uint8_t
	{
		KEY_REPEAT
	};

	enum class EKeyEvent: uint8_t
	{
		KEY_PRESS,
		KEY_RELEASE,
	};



}