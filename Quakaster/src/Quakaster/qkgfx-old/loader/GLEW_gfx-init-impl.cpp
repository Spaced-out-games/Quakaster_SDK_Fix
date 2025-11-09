#include "../gfx-init.h"
#include <GL/glew.h> 

namespace qk::gfx::loader
{
	Error load()
	{
		GLenum err = glewInit();
		if(err != GLEW_OK) return { Error_t::GFX_API_LOADER_FAILURE, (const char*)glewGetErrorString(err) };
		return { Error_t::NONE, nullptr };

	}
}