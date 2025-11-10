#include "VAO.h"


namespace qk::gfx
{
	
	VAO::VAO() {}

	VAO::VAO(GLuint ID)
	{
		m_vao = 0;
	}

	VAO::~VAO()
	{
		destroy();
	}

	void VAO::init()
	{
		glGenVertexArrays(1, &m_vao);
	}

	void VAO::bind()
	{
		glBindVertexArray(m_vao);
	}

	void VAO::unbind()
	{

	}

	void VAO::destroy()
	{
		if (m_vao != 0)
		{
			glDeleteVertexArrays(1, &m_vao);
			m_vao = 0;
		}
	}

	VAO::operator GLuint()
	{
		return m_vao;
	}
}
