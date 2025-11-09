#include "gfx-Context.h"
#include "Error.h"
#include <SDL.h>
#include <GL/glew.h>
#include "Window.h"


namespace qk::gfx
{
    
    Error Context::init(Window& win)
    {
        m_Handle = SDL_GL_CreateContext(win);
        if (!m_Handle)
        {
            m_Handle = nullptr;
            return { Error_t::GFX_API_INIT_FAILURE, SDL_GetError() };
        }
        SDL_GL_MakeCurrent(win, m_Handle);

        return Error{ Error_t::NONE, nullptr };
    }

    void Context::clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Context::swap(Window& win)
    {
        SDL_GL_SwapWindow(win);
    }

    void Context::destroy()
    {
        if (m_Handle)
        {
            SDL_GL_DeleteContext(m_Handle);
            m_Handle = nullptr;
        }
    }
    
}