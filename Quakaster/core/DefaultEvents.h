#pragma once
#include "IEvent.h"

namespace qk {
	struct KeyEvent : IEvent {
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

	struct MouseEvent : IEvent {
		inline int& button() { return *reinterpret_cast<int*>(&m_Payload[0]); }
		inline int& action() { return *reinterpret_cast<int*>(&m_Payload[4]); }
		inline int& mods() { return *reinterpret_cast<int*>(&m_Payload[8]); }
		// last 4 bytes unused, can be reserved for future or padding
	};

	struct MouseMoveEvent : IEvent {
		inline float& x() { return *reinterpret_cast<float*>(&m_Payload[0]); }
		inline float& y() { return *reinterpret_cast<float*>(&m_Payload[4]); }
		// optional: delta_x and delta_y in next 8 bytes if you want
	};

}