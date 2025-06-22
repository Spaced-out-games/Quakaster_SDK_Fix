#pragma once
#include "../../Core.h"

#include "import.h"
#include <vector>
namespace qkg {

	struct Window;

	class QK_API GraphicsPipeline
	{
		public:
			SDL_GLContext m_GLContext;
			GraphicsPipeline();
			~GraphicsPipeline();
			inline void init(Window& window);
			inline void init(SDL_Window* window);
			const SDL_GLContext& context();
	};
}