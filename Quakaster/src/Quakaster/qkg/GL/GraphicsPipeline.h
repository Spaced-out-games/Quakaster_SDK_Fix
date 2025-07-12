#pragma once
#include "../../Core.h"
#include "../../logging.h"

#include <SDL.h>

#include <vector>
namespace qkg {


	class QK_API GraphicsPipeline
	{
		public:
			SDL_GLContext m_GLContext;
			GraphicsPipeline();
			~GraphicsPipeline();
			inline void init(SDL_Window* window);
			//const SDL_GLContext& context();
			explicit operator SDL_GLContext() const;
	};
}