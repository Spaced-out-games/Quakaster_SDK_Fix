#include "Event.h"


namespace qk::io
{
	uint16_t& Event::variant_code()
	{
		return m_Header.variant;
	}
	EEventCategory& Event::category()
	{
		return m_Header.category;
	}
	uint8_t& Event::type_code()
	{
		return m_Header.type;
	}

	//---------------------------------------------------------- contracts ----------------------------------------------------------//
	
	
	std::string Event::to_string(Event& evt)
	{
		return "Event{}";
	}
	bool Event::is_same_category(Event& evt)
	{
		// all events are events
		return true;
	}
	bool Event::is_same_type(Event& evt)
	{
		// all events are events
		return true;
	}
	Event* Event::event_cast(Event& evt)
	{
		return &evt;
	}
	Event::operator Event& ()
	{
		return *this;
	}


	//------------------------------------------------------------------------------------------------------------------------------//


}