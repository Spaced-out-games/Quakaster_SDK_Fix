#include "Context.h"
#include "Window.h"
#include <sstream>

using namespace qk;

namespace qkg {
	Context::Context()
	{

	}

	Context::~Context()
	{
		std::stringstream ss;
		ss << "CRITICAL     qkg::~Context() called at 0x";
		ss << (void*)this;
		qk::log(ss.str(), LOG_INFO, CAT_GRAPHICS);
		if (m_GLContext)						  
		{										  
			SDL_GL_DeleteContext(m_GLContext);	  
		}										  
	}											  

	void Context::init(Window& window)
	{
		m_GLContext = SDL_GL_CreateContext(window.m_Window);
		SDL_GL_MakeCurrent(window.m_Window, m_GLContext);
		SDL_GL_SetSwapInterval(1);
	}

	
}