#pragma once
#include <stdint.h>

namespace qk::io
{
	enum Keycode: uint16_t
	{
		// tbd, but for now, these'll work
		KEY_A = 'a',
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,

		KEY_0 = '0',
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,

		KEY_EXCLAIMATION = '!',
		KEY_AT = '@',
		KEY_HASH = '#',
		KEY_DOLLAR = '$',
		KEY_PERCENT = '%',
		KEY_CAROT = '^',
		KEY_AMPERSAND = '&',
		KEY_ASTERISK = '*',
		KEY_LPAREN = '(',
		KEY_RPAREN = ')',
		KEY_LCURLY = '{',
		KEY_RCURLY = '}',
		KEY_LBRACKET = '[',
		KEY_RBRACKET = ']',
		KEY_QUOTE1 = '\'',
		KEY_QUOTE2 = '"',
		KEY_GREATER_THAN = '>',
		KEY_LESS_THAN = '<',
		KEY_TAB = '\t',
	};

	enum class EKeyRepeatEvent: uint8_t
	{
		KEY_REPEAT
	};

	enum class EKeyEvent: uint8_t
	{
		KEY_PRESS,
		KEY_RELEASE,
	};

	struct FKeyEventPayload
	{
		int modifiers;
		
	};

}