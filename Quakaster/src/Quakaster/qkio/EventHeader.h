#pragma once
#include "../Core.h"
#include "EEventCategory.h"


namespace qk::io
{
	struct EventHeader
	{
		EEventCategory category;
		uint8_t type;
		uint16_t variant;
	};
}