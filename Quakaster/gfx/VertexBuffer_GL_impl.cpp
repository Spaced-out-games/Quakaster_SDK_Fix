#include "VertexBuffer.h"
#include "GL/glew.h"

namespace gfx {


	VertexBuffer_impl::VertexBuffer_impl()
	{


	}

	void VertexBuffer_impl::init_impl(const void* data, size_t count, size_t elem_size, unsigned int usage) {
		if (m_Handle != NULL_HANDLE) {
			__debugbreak();
		}
		m_Count = count;
		glGenBuffers(1, &m_Handle);
		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
		glBufferData(GL_ARRAY_BUFFER, count * elem_size, data, usage);
	}

	VertexBuffer_impl::~VertexBuffer_impl()
	{
		if (m_Handle != NULL_HANDLE) {
			glDeleteBuffers(1, &m_Handle);
		}
	}

	void VertexBuffer_impl::bind_impl() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
	}
	void VertexBuffer_impl::unbind_impl() const {
		#ifdef _DEBUG
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		#endif
	}

	




} // namespace gfx