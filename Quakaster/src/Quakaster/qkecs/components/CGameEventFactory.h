#pragma once
#include "../../qk/QKTL.h"
#include <SDL_events.h>
#include "GameEvent.h"



/// <summary>
/// Takes in an SDL_Event and generates a game event.
/// </summary>

template <class GameEventCommand_t>
struct TGameEventFactory_SDL
{
	using Event_t = qk::GameEvent_t<GameEventCommand_t>;

	func_ptr_t<Event_t, const SDL_Event&> m_Converter;

	Event_t operator()(const SDL_Event& evt)
	{
		if (m_Converter) return m_Converter(evt);
		return {};
	}

};

using CGameEventFactory_SDL = TGameEventFactory_SDL<qk::EGameEventCommand_t>;
