#include "SDL2_Event_impl.h"

namespace qk::io
{
	Event QK_API from_SDL_Event(const SDL_Event& evt)
	{
		switch (evt.type)
		{
			case SDL_QUIT:
			{

			}
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				KeyPressEvent kp{ (uint16_t)evt.key.keysym.scancode, evt.key.keysym.sym, 1 };
				return (Event)kp;
			}
			case SDL_MOUSEMOTION:
			{	
				MouseMoveEvent mv(evt.motion.xrel, evt.motion.yrel);
				return (Event)mv;
			}
			

		
			default:
				break;
		}
		return Event{};
	}

}