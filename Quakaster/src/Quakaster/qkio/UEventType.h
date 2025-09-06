#pragma once
#include <memory>
#include <stdint.h>
#include "EventTypes\EAppEvent.h"
#include "EventTypes\EClientEvent.h"
#include "EventTypes\EGameAction.h"
#include "EventTypes\EKeyEvent.h"
#include "EventTypes\EMouseEvent.h"
#include "EventTypes\EMouseMoveEvent.h"
#include "EventTypes\EServerEvent.h"
#include "EventTypes\EWindowEvent.h"

namespace qk::io
{


	union UEventType
	{
		uint8_t raw;
		EMouseEvent mouse_event;
		EMouseMoveEvent mouse_move_event;
		EKeyEvent key_event;
		EClientEvent client_event;
		EServerEvent server_event;
		EAppEvent app_event;
		EWindowEvent window_event;
		EGameAction game_action;
		// add more event types as-needed...

	};

}