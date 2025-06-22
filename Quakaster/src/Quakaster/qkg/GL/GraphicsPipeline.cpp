#include "GraphicsPipeline.h"
#include "Window.h"
#include <sstream>

using namespace qk;

namespace qkg {
	GraphicsPipeline::GraphicsPipeline()
	{

	}

	GraphicsPipeline::~GraphicsPipeline()
	{
		std::stringstream ss;
		ss << "CRITICAL     qkg::~GraphicsPipeline() called at 0x";
		ss << (void*)this;
		qk::log(ss.str(), LOG_INFO, CAT_GRAPHICS);
		if (m_GLContext)						  
		{										  
			SDL_GL_DeleteContext(m_GLContext);	  
		}										  
	}

	void GraphicsPipeline::init(SDL_Window* window)
	{
		m_GLContext = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, m_GLContext);
		SDL_GL_SetSwapInterval(1);
	}

	void GraphicsPipeline::init(Window& window)
	{
		init(window.m_Window);
	}
	const SDL_GLContext& GraphicsPipeline::context() { return m_GLContext; }

	
}