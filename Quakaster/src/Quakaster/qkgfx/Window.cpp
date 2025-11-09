#include "Window.h"

namespace qk::gfx
{


	Error Window::init(const char* title, int x, int y, int w, int h, uint32_t flags)
	{

		// Create the SDL window inside the wrapper
		m_Handle = SDL_CreateWindow(title, x, y, w, h, flags);
		if (!m_Handle)
		{
			return { Error_t::PLATFORM_WINDOW_CREATE_ERROR, SDL_GetError() };
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

		if (m_Handle)
			SDL_DestroyWindow(m_Handle);


		// prevents UAF
		m_Handle = nullptr; 
	}
	Window::~Window()
	{
		destroy();
	}

	bool Window::is_valid()
	{
		return m_Handle != nullptr;
	}

	void Window::resize(int width, int height)
	{
		if (!m_Handle) return;

		SDL_SetWindowSize(m_Handle, width, height);
		m_Width = width;
		m_Height = height;
	}

	void Window::swap()
	{
		if (!m_Handle) return;

		SDL_GL_SwapWindow(m_Handle);
	}

	int Window::width() const { return m_Width; }
	int Window::height() const { return m_Height; }
	const char* Window::title() const { return m_Title; }



}