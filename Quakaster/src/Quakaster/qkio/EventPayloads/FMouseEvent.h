#pragma once
#include <stdint.h>
#include "../../qkmath/vec2.h"


namespace qk::io
{
	struct FMouseEventPayload
	{
		vec2 mouse_pos;
		uint8_t button;
		uint8_t clicks;
	};
}