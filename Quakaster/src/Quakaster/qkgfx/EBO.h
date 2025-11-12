#pragma once
#include "../Core.h"
#include <GL/glew.h>
#include "Error.h"

namespace qk::gfx
{
	struct QK_API EBO
	{
		GLuint m_ebo = 0;
		uint32_t m_IndexCount = 0;
		EBO();
		EBO(GLuint ebo);
		Result init();
		void bind();
		void destroy();
		static void unbind();
		void upload(uint32_t* indices, size_t size, GLenum usage);
	};
}