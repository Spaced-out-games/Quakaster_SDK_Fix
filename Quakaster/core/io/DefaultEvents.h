#pragma once
#include "Event.h"

namespace qk {
	struct KeyEvent : Event {
		inline int& key() {
			return *((int*)m_Payload);
		}
		inline int& scancode() {
			return *((int*)m_Payload + 1);
		}

		inline int& mods() {
			return *((int*)m_Payload + 2);
		}
	};

	struct MouseEvent : Event {
		inline int& button() { return *((int*)m_Payload); }
		inline int& action() { return *((int*)m_Payload + 1);; }
		inline int& mods() { return *((int*)m_Payload + 2); }
		// last 4 bytes unused, can be reserved for future or padding
	};

	struct MouseMoveEvent : Event {
		inline float& x() { return *((float*)m_Payload); }
		inline float& y() { return *((float*)m_Payload + 1); }
		// optional: delta_x and delta_y in next 8 bytes if you want
	};


}