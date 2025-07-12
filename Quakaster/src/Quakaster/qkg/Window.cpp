#include "Window.h"
#include <SDL.h>
#include <sstream>
#include "../logging.h"
#include <stdexcept>


using namespace qk;

namespace qkg
{
	Window::Window(): m_Window(nullptr), m_Width(0), m_Height(0)
	{
		// since this is a defualt constructor that is just for allocating memory, it's not appropriate to log the allocation
	}

	void Window::init()
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
			throw std::runtime_error("SDL_CreateWindow returned nullptr");
		}

	}

	void Window::vertical_sync(int interval)
	{
		SDL_GL_SetSwapInterval(interval);
	}


	Window::~Window()
	{
		if (!m_Window)
		{
			throw std::runtime_error("~Window() called when m_Window was nullptr.");
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
		if (!m_Window)  throw std::runtime_error("Window::swap() called at nullptr");
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
	 Window::operator SDL_Window* () const {
		 return m_Window;
	 }



}