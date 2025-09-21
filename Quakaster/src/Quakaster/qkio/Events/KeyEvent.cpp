#pragma once
#include "KeyEvent.h"
#include <stdint.h>

namespace qk::io
{
	

	int& KeyPressEvent::keycode() { return from_payload<int, 0>(); }
	int& KeyPressEvent::modifiers() { return from_payload<int, sizeof(int)>(); }

	uint16_t& KeyPressEvent::scancode() { return from_variant<uint16_t>(); }



	KeyPressEvent::KeyPressEvent(uint16_t scan_key, int key_code, uint8_t type):
		Event(
			EEventCategory::KEYBOARD_EVENT | EEventCategory::BUTTON_EVENT,
			type,
			0
		)
	{
		
		scancode() = scan_key;
		keycode() = key_code;

	}

	
	bool KeyPressEvent::is_same_category(Event& evt)
	{
		return evt.category() & (EEventCategory::KEYBOARD_EVENT | EEventCategory::BUTTON_EVENT);
	}
	bool KeyPressEvent::is_same_type(Event& evt)
	{
		return evt.type_code() <= 1;
	}
	KeyPressEvent* KeyPressEvent::event_cast(Event& evt)
	{
		if (KeyPressEvent::is_same_category(evt) && KeyPressEvent::is_same_type(evt))
		{
			return reinterpret_cast<KeyPressEvent*>(&evt);
		}
		return nullptr;
	}


	
	std::string KeyPressEvent::to_string(Event& evt)
	{
		KeyPressEvent* kpevt = event_cast(evt);
		if (kpevt)
		{
			return "KeyPressEvent {" + std::to_string(kpevt->keycode()) + "}";
		}
		else
		{
			return "<invalid cast to KeyPressEvent>";
		}
	}



}