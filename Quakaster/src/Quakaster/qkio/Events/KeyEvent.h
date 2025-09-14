#pragma once
#include "../Event.h"
#include "../../Core.h"
#include <string>

namespace qk::io
{
	struct QK_API KeyPressEvent : Event
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

			// Upcasts to a generic event. It will always be safe, so long as the reference is in scope
			operator Event& () { return *this; }

			// Attempts to downcast to a key event
			inline static KeyPressEvent* try_cast_impl(Event& evt);

			inline static bool is_impl(const Event& evt);


			// Convert to string
			static std::string to_string_impl(Event& evt);
	};
}