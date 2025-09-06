#pragma once
#include "EventPayloads\FKeyEventPayload.h"
#include "EventPayloads\FMouseMoveEventPayload.h"
#include "EventPayloads\FMouseEvent.h"
namespace qk::io
{
	struct UEventPayload
	{
		union
		{
			FKeyEventPayload key_event;
			FMouseMoveEventPayload mouse_move_event;
			FMouseEventPayload mouse_event;
		};

	};
}