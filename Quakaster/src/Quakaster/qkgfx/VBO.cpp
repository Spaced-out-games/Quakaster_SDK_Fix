#include "VBO.h"

namespace qk::gfx
{
	
	VBO::VBO()
	{

	}
	VBO::VBO(GLuint vbo)
	{
		m_vbo = vbo;
	}
	VBO::~VBO()
	{
		destroy();
	}
	void VBO::init()
	{
		glGenBuffers(1, &m_vbo);
	}
	void VBO::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	}
	void VBO::destroy()
	{
		if (m_vbo != 0)
		{
			glDeleteBuffers(1, &m_vbo);
			m_vbo = 0; // mark deleted
		}
	}

	void VBO::upload_vertices_impl(const void* vertices, const size_t num_vertices, const size_t vertex_size, const GLenum usage)
	{
		glBufferData(GL_ARRAY_BUFFER, num_vertices * vertex_size, vertices, usage);
	}


	VBO::operator GLuint()
	{
		return m_vbo;
	}
}