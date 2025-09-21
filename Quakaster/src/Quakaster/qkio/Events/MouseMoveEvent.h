#pragma once
#include "../Event.h"
#include "../../Core.h"
#include <string>
#include "../../qkmath/vec2.h"

namespace qk::io
{

	const vec2& get_mouse_absolute_position();
	
	void set_mouse_absolute_position(float x, float y);

	struct QK_API MouseMoveEvent : Event
	{




		vec2& delta_position();

		MouseMoveEvent(float dx, float dy);
		MouseMoveEvent(vec2 delta);


		static std::string to_string(Event& evt);
		static bool is_same_category(Event& evt);
		static bool is_same_type(Event& evt);
		static MouseMoveEvent* event_cast(Event& evt);

	};
	
	QKIO_ASSERT(MouseMoveEvent)


}