#pragma once
#include "KeyEvent.h"
#include <stdint.h>

namespace qk::io
{
	
	std::string KeyPressEvent::to_string_impl(Event& evt)
	{
		char buf[64]; // stack buffer
		KeyPressEvent& kv = *(KeyPressEvent*)&evt;

		std::snprintf(
			buf,
			sizeof(buf),
			"KeyPressEvent{ key: %d, scancode: %u }",
			kv.keycode(),
			kv.scancode()
		);
		return std::string(buf);
	}
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

	bool KeyPressEvent::is_impl(const Event& evt)
	{
		bool control;
		control = evt.category() == (EEventCategory::KEYBOARD_EVENT | EEventCategory::BUTTON_EVENT);
		return control;
	}


	KeyPressEvent* KeyPressEvent::try_cast_impl(Event& evt)
	{
		if (is_impl(evt))
		{
			return (KeyPressEvent*) &evt;
		}
		return nullptr;
	}
	



}