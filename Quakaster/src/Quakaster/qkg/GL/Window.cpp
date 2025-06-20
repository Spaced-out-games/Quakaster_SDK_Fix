#include "Window.h"
#include <SDL.h>
#include <sstream>

using namespace qk;

namespace qkg
{
	Window::Window(): m_Window(nullptr)
	{
		// since this is a defualt constructor that is just for allocating memory, it's not appropriate to log the allocation
	}

	bool Window::init()
	{
		m_Window = SDL_CreateWindow(
			m_Title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_Width,
			m_Height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		);

		if (!m_Window) {
			fprintf(stderr, "Failed to create SDL_Window: %s\n", SDL_GetError());
			exit(1);
		}

		return m_Window != nullptr;
	}

	void Window::vertical_sync(int interval)
	{
		SDL_GL_SetSwapInterval(interval);
	}


	Window::~Window()
	{
		if (!m_Window)
		{
			qk::log("~Window() at nullptr", LOG_ERROR_SEVERE, CAT_GRAPHICS);
			return;
		}

		std::stringstream ss;
		ss << "~Window() at 0x" << static_cast<void*>(this);
		log(ss.str(), LOG_INFO, CAT_GRAPHICS);
		SDL_DestroyWindow(m_Window);
	}

	void Window::swap()
	{
		#ifdef _DEBUG
		if (!m_Window) qk::log("Window::swap() ran on uninitialized window!", LOG_ERROR_CRITICAL, CAT_GRAPHICS);
		#endif
		SDL_GL_SwapWindow(m_Window);
	}


	 void make_window(Window& window, const int width, const int height, const std::string title) {
		log("Created Window", LOG_INFO, CAT_GRAPHICS);
		window.m_Height = height;
		window.m_Width = width;
		window.m_Title = title;
		window.init();
	}


}