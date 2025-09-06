#pragma once
#include <SDL.h>
#include "../EventTypes/EKeycode.h"

namespace qk::io
{
    template <>
    inline EKeycode make_keycode<SDL_Keycode>(const SDL_Keycode keycode)
    {
        switch (keycode)
        {
        case SDLK_RETURN:    return EKeycode::KEY_RETURN;
        case SDLK_ESCAPE:    return EKeycode::KEY_ESCAPE;
        default:             return EKeycode::KEY_UNKNOWN;
        }
    }
}