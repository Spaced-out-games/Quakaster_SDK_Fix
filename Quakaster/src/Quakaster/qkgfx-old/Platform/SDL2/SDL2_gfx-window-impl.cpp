#include "../../gfx-window.h"
#include <SDL.h>

namespace qk::gfx::platform
{
	struct Window_handle_t {
		SDL_Window* hdl = nullptr;

	};


	Error Window::init(const char* title, int x, int y, int w, int h, uint32_t flags)
	{
		// Allocate the handle
		m_Handle = new Window_handle_t{};
		if (!m_Handle)
			return { Error_t::PLATFORM_WINDOW_CREATE_ERROR, "Failed to allocate handle" };

		// Create the SDL window inside the wrapper
		m_Handle->hdl = SDL_CreateWindow(title, x, y, w, h, flags);
		if (!m_Handle->hdl)
		{
			Error result = { Error_t::PLATFORM_WINDOW_CREATE_ERROR, SDL_GetError() };
			delete m_Handle;
			m_Handle = nullptr;
			return result;
		}

		// Save window properties
		m_Title = title;
		m_X = x;
		m_Y = y;
		m_Width = w;
		m_Height = h;

		return { Error_t::NONE, nullptr };
	}
	void Window::destroy()
	{
		if (!m_Handle) return;

		if (m_Handle->hdl)
			SDL_DestroyWindow(m_Handle->hdl);

		delete m_Handle;
		m_Handle = nullptr;
	}
	Window::~Window()
	{
		destroy();
	}

	bool Window::is_valid()
	{
		return m_Handle != nullptr && m_Handle->hdl != nullptr;
	}

	void Window::resize(int width, int height)
	{
		if (!m_Handle || !m_Handle->hdl) return;

		SDL_SetWindowSize(m_Handle->hdl, width, height);
		m_Width = width;
		m_Height = height;
	}

	void Window::swap()
	{
		if (!m_Handle || !m_Handle->hdl) return;

		SDL_GL_SwapWindow(m_Handle->hdl);
	}

	int Window::width() const { return m_Width; }
	int Window::height() const { return m_Height; }
	const char* Window::title() const { return m_Title; }
	void* Window::handle() { return m_Handle->hdl; }



}