#include "../../gfx-api.h"
#include "../../gfx-core.h"
#include <SDL.h>
#include <GL/glew.h>
#include "../../gfx-window.h"


namespace qk::gfx
{
    struct QK_API Context_handle_t {
        SDL_GLContext m_Context = nullptr;
    };

    Error Context::init(platform::Window& win)
    {
        SDL_Window* sdlWin = (SDL_Window*)win.handle(); // <- get real SDL_Window*
        m_Handle = new Context_handle_t{};
        m_Handle->m_Context = SDL_GL_CreateContext(sdlWin);
        if (!m_Handle->m_Context)
        {
            delete m_Handle;
            m_Handle = nullptr;
            return { Error_t::GFX_API_INIT_FAILURE, SDL_GetError() };
        }
        SDL_GL_MakeCurrent(sdlWin, m_Handle->m_Context);

        return Error{ Error_t::NONE, nullptr };
    }

    void Context::clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Context::swap(platform::Window& win)
    {
        SDL_GL_SwapWindow((SDL_Window*)win.handle());
    }

    void Context::destroy()
    {
        if (m_Handle)
        {
            if (m_Handle->m_Context)
                SDL_GL_DeleteContext(m_Handle->m_Context);
            delete m_Handle;
            m_Handle = nullptr;
        }
    }
}