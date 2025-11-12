#include "EBO.h"

namespace qk::gfx
{

	EBO::EBO()
	{

	}
	EBO::EBO(GLuint ebo)
	{
		m_ebo = ebo;
	}
	Result EBO::init()
	{
		glGenBuffers(1, &m_ebo);
		GLenum err = glGetError(); // query OpenGL for error
		if (err != GL_NO_ERROR)
		{
			return Error{ Error_t::GFX_VERTEX_BUFFER_INIT_ERROR, (const char*)glewGetErrorString(err) };
		}
		return Error{ Error_t::NONE, nullptr };

	}
	void EBO::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	}
	void EBO::destroy()
	{

	}
	void EBO::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void EBO::upload(uint32_t* indices, size_t size, GLenum usage)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, usage);
		m_IndexCount = size;
	}
}