#pragma once
#include "../../Core.h"

#include "import.h"
#include <vector>
namespace qkg {

	struct Window;

	class QK_API Context
	{
		public:
			SDL_GLContext m_GLContext;
			Context();
			~Context();
			void init(Window& window);
	};
}