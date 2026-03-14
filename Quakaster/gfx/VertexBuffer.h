#pragma once
#include "gfx.h"


namespace gfx {
	// TODO: Separate initialization from uploads

	class QK_API VertexBuffer_impl {
		protected:
			Handle m_Handle = NULL_HANDLE;
			unsigned int m_Count = 0;
			VertexBuffer_impl();
			~VertexBuffer_impl();
			void init_impl(const void* data, size_t count, size_t elem_size, unsigned int usage);
			void bind_impl() const;
			void unbind_impl() const;
	};


	template <class vertex_t>
	struct VertexBuffer : VertexBuffer_impl {
		size_t elem_size() const {
			return sizeof(vertex_t);
		}

		size_t count() const {
			return m_Count;
		}

		size_t size_bytes() const {
			return count() * elem_size();
		}


		void init(const vertex_t* data, size_t count, unsigned int usage) {
			init_impl(data, count, sizeof(vertex_t), usage);
		}

		void bind() const { bind_impl(); }
		void unbind() const { unbind_impl(); }

	};

}