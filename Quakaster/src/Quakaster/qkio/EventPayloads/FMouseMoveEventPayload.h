#pragma once
#include <stdint.h>
#include "../../qkmath/vec2.h"


namespace qk::io
{
	struct FMouseMoveEventPayload
	{
		vec2 delta_pos;

	};
}