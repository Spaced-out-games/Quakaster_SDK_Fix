#pragma once
#include <memory>
#include <stdint.h>
#include "EEventCategory.h"
#include "UEventType.h"
#include "UEventPayload.h"

namespace qk::io
{

	

	struct FEventHeader
	{
		

		EEventCategory category = {};
		UEventType type = {};
		uint16_t variant = {};

	};


	// safety check to make sure that EventHeader can be safely cast to uint32_t
	static_assert(sizeof(FEventHeader) == 4, "CRITICAL ERROR: EventHeader is not 32 bits big!");


	


	struct Event
	{
		FEventHeader header;
		UEventPayload payload;
	};

	template <class framework_event_t>
	inline Event make_event(const framework_event_t& evt) noexcept
	{
		return {};
	}

}

// hashing a header
namespace std {
	template <>
	struct hash<qk::io::FEventHeader>
	{
		std::size_t operator()(const qk::io::FEventHeader& t) const noexcept
		{
			std::size_t result = 0;
			std::memcpy(&result, &t, sizeof(qk::io::FEventHeader));
			return result;
		}
	};
}