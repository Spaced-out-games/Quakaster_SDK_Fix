#pragma once
#include "../Event.h"
#include "../../Core.h"
#include <string>

namespace qk::io
{
	struct QK_API KeyPressEvent: Event
	{

		


		public:
			// Get the keycode
			int& keycode();

			// get the hey modifiers
			int& modifiers();

			// get the scancode
			uint16_t& scancode();

			// construct it
			KeyPressEvent(uint16_t scan_key, int key_code, uint8_t type);

			



			static std::string to_string(Event& evt);
			static bool is_same_category(Event& evt);
			static bool is_same_type(Event& evt);
			static KeyPressEvent* event_cast(Event& evt);


	};

	QKIO_ASSERT(KeyPressEvent)
}