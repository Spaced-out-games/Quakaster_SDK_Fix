#pragma once
#include "EEventType.h"
#include "EEventCategory.h"

namespace qk::io
{
	struct EventHeader
	{
		const EEventCategory	category;
		const EEventType		type;
		uint32_t				variant;
		uint64_t				hash();
		EventHeader(EEventCategory category, EEventType type, uint32_t variant);
	};
}