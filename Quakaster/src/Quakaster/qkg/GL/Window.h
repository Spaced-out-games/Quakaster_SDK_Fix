#pragma once

#include "../../Core.h"
#include <string>



struct SDL_Window;

namespace qkg
{

	class QK_API Window
	{

		friend void QK_API make_window(Window& window, const int width, const int height, const std::string title);
		friend class Context;
		private:
			int m_Height;
			int m_Width;
			std::string m_Title;

		public:
			SDL_Window* m_Window;

			Window();
			~Window();
			bool init();
			void vertical_sync(int);
			void swap();
	};

	// This just forces the user to construct and initialize it, and prevents trying to initialize it before SDL is ready
	void QK_API make_window(Window& window, const int width, const int height, const std::string title);

}