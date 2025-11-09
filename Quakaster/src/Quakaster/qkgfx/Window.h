#pragma once
#include "../Core.h"
#include "Error.h"
#include <SDL.h>

// Declares a platform-agnostic API for creating a window
namespace qk::gfx
{
	// consider making it a class

	class QK_API Window
	{
		
		
		SDL_Window* m_Handle = nullptr;
		const char* m_Title = nullptr;
		int m_X = 0;
		int m_Y = 0;
		int m_Width = 0;
		int m_Height = 0;
		// poller_t* m_Poller;

	public:
		Window() = default;
		~Window();
		Error init(const char* title, int x, int y, int w, int h, uint32_t flags);
		void destroy();
		bool is_valid();
		// void poll_events();
		void resize(int width, int height);
		void swap();
		int width() const;
		int height() const;
		const char* title() const;
		operator SDL_Window* () { return m_Handle; }
	};


}