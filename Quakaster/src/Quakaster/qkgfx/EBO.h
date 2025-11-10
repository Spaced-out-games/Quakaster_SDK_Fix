#pragma once
#include "../Core.h"
#include <GL/glew.h>

namespace qk::gfx
{
	struct QK_API EBO
	{
		GLuint m_ebo = 0;
		EBO();
		EBO(GLuint ebo);
		void init();
		void bind();
		void destroy();
		static void unbind();
		void upload(uint32_t* indices, size_t size, GLenum usage);
	};
}