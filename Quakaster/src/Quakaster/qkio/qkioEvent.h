#pragma once
#include <memory>
#include <stdint.h>
#include "Events\EAppEvent.h"
#include "Events\EClientEvent.h"
#include "Events\EGameAction.h"
#include "Events\EKeyEvent.h"
#include "Events\EMouseEvent.h"
#include "Events\EMouseMoveEvent.h"
#include "Events\EServerEvent.h"
#include "Events\EWindowEvent.h"

namespace qk::io
{
	enum class EEventCategory: uint8_t
	{
		NULL_EVENT,
		MOUSE_EVENT,
		MOUSE_MOVE_EVENT,
		KEY_EVENT,
		KEY_REPEAT_EVENT,
		CLIENT_EVENT,
		SERVER_EVENT,
		APP_EVENT,
		WINDOW_EVENT,
		GAME_ACTION
	}; 
	
	union UEventType
	{
		EMouseEvent mouse_event;
		EKeyEvent key_event;
		EClientEvent client_event;
		EServerEvent server_event;
		EAppEvent app_event;
		EWindowEvent window_event;
		EGameAction game_action;
		// add more event types as-needed...

	};

	


	
	
	
	

	

	struct EventHeader
	{
		

		EEventCategory category = {};
		UEventType type = {};

		/// <summary>
		///  Used to further granulate events. This could let you pass SV_DISCONNECT 404, which could
		///  connect to a unique callback, this could be a keycode, this could be a USE_ITEM ID for
		/// unique weapon use callbacks...Meant to make hash() return a unique hash key code
		/// </summary>
		uint16_t variant = {};


		inline uint32_t hash() const;

		

	};
	// safety check to make sure that EventHeader can be safely cast to uint32_t
	static_assert(sizeof(EventHeader) == 4, "CRITICAL ERROR: EventHeader is not 32 bits big!");


	struct EventPayload
	{
		union
		{
			uint8_t raw[12];
			// more members as needed
		};

	};
	


	struct Event
	{
		EventHeader header;
		EventPayload payload;

	};

}