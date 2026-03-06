#pragma once
#include "SSBO.h"
#include "GL/glew.h"

namespace gfx {

	

	bool SSBO_impl::bind_impl() {
		if (!(m_Mode & ESSBOAccessMode::Read)) return false;
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Handle);
		return true;
	}

	void SSBO_impl::unbind() {
		// should always be safe
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	void SSBO_impl::destroy() {
		
		glDeleteBuffers(&m_Handle);
	}

	void SSBO_impl::push_back_impl(size_t elem_size, const void* data) {
		if (m_Size >= m_Capacity) {
			reserve_impl(std::max(m_Capacity * 2, size_t(512)), elem_size);
		}

		if (m_Mode & ESSBOAccessMode::Write && m_Data) {
			memcpy((char*)m_Data + m_Size * elem_size, data, elem_size);
			m_Size++;
		}
		else {
			// write not allowed
		}
	}

	bool SSBO_impl::set_mode(ESSBOAccessMode mode) {
		bool result = 0;
		if (!(m_Mode & ESSBOAccessMode::ReadLock)) { 
			result |= (mode & ESSBOAccessMode::Read) != (m_Mode & ESSBOAccessMode::Read);
			m_Mode |= mode & ESSBOAccessMode::Read;
			
		}
		if (!(m_Mode & ESSBOAccessMode::ReadLock)) {
			result |= (mode & ESSBOAccessMode::Write) != (m_Mode & ESSBOAccessMode::Write);
			m_Mode |= mode & ESSBOAccessMode::Read;

		}
		return result;
	}


	void SSBO_impl::reserve_impl(size_t new_capacity, size_t elem_size) {
		if (new_capacity <= m_Capacity) return;
		unsigned int new_handle;
		glGenBuffers(1, &new_handle);

		// Allocate new storage
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, newHandle);
		glBufferData(GL_SHADER_STORAGE_BUFFER,
			new_capacity * elem_size,
			nullptr,
			GL_DYNAMIC_DRAW);

		m_Data = glMapBufferRange(
			GL_SHADER_STORAGE_BUFFER,
			0,
			new_capacity * elem_size,
			GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
		);

		// Copy old data if any
		if (m_Handle != 0)
		{
			glBindBuffer(GL_COPY_READ_BUFFER, m_Handle);
			glBindBuffer(GL_COPY_WRITE_BUFFER, new_handle);

			glCopyBufferSubData(GL_COPY_READ_BUFFER,
				GL_COPY_WRITE_BUFFER,
				0, 0,
				m_Size * elem_size);

			glDeleteBuffers(1, &m_Handle);
		}

		m_Handle = newHandle;
		m_Capacity = newCapacity;

	}

	void SSBO_impl::capacity() {
		return m_Capacity;
	}
	void SSBO_impl::size() {
		return m_Size;
	}
	void* SSBO_impl::read_impl() {
		if (m_Mode & ESSBOAccessMode::Read) return m_Data;
		return nullptr;
	}
	void* SSBO_impl::write_impl() {
		if (m_Mode & ESSBOAccessMode::Write) return m_Data;
		return nullptr;
	}
	

}