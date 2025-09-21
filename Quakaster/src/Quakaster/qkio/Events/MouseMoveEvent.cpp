#include "MouseMoveEvent.h"


namespace qk::io
{
	static vec2 g_MousePosition;


	const vec2& get_mouse_absolute_position()
	{
		return g_MousePosition;
	}

	void set_mouse_absolute_position(float x, float y)
	{
		g_MousePosition = { x, y };
	}

	vec2& MouseMoveEvent::delta_position()
	{
		return from_payload<vec2, 0>();
	}


	MouseMoveEvent::MouseMoveEvent(float dx, float dy):
		Event(EEventCategory::MOUSE_EVENT | EEventCategory::AXIS_EVENT,1, 0)
	{
		delta_position() = { dx, dy };
	}
	MouseMoveEvent::MouseMoveEvent(vec2 delta)
	{
		delta_position() = delta;
	}
	
	bool MouseMoveEvent::is_same_category(Event& evt)
	{
		return evt.category() == (EEventCategory::MOUSE_EVENT | EEventCategory::AXIS_EVENT);
	}

	bool MouseMoveEvent::is_same_type(Event& evt)
	{
		return evt.type_code() == 1;
	}
	MouseMoveEvent* MouseMoveEvent::event_cast(Event& evt)
	{
		if (MouseMoveEvent::is_same_category(evt) && MouseMoveEvent::is_same_type(evt))
		{
			return reinterpret_cast<MouseMoveEvent*>(&evt);
		}
		return nullptr;
	}

	std::string MouseMoveEvent::to_string(Event& evt)
	{
		MouseMoveEvent* mv = event_cast(evt);
		if (mv)
		{
			vec2& dp = mv->delta_position();
			return "MouseMoveEvent {" + std::to_string(dp.x) + ", " + std::to_string(dp.y) + "}";
		}
		return "<invalid cast to MouseMoveEvent>";
	}


}