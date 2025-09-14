#include "Event.h"


namespace qk::io
{
	const EEventCategory Event::category() const { return m_Header.category; }
	const uint8_t Event::type() { return m_Header.type; }
	Event* Event::try_cast_impl(Event& evt)
	{
		return &evt;
	}

	// all events are events.
	bool Event::is_impl(Event& evt)
	{
		return 1;
	}

	std::string Event::to_string_impl(Event& evt)
	{

		return "Event{???}";
	}
}