#include "GraphicsPipeline.h"
#include "../Window.h"
#include <sstream>
#include <stdexcept>


using namespace qk;

namespace qkg {
	GraphicsPipeline::GraphicsPipeline(): m_GLContext(nullptr)
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
		else
		{
			throw std::runtime_error("SDL failed to initialize: " + std::string(SDL_GetError()));

		}
	}

	void GraphicsPipeline::init(SDL_Window* window)
	{
		m_GLContext = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, m_GLContext);
		SDL_GL_SetSwapInterval(1);
	}


	//const SDL_GLContext& GraphicsPipeline::context() { return m_GLContext; }

	GraphicsPipeline::operator SDL_GLContext() const
	{
		return m_GLContext;
	}
	
}