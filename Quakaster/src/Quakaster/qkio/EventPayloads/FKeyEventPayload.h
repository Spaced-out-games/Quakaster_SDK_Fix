#pragma once
#include <stdint.h>


namespace qk::io
{
	struct FKeyEventPayload
	{
		int keycode;
		uint16_t modifiers;
		bool repeat;

	};
}