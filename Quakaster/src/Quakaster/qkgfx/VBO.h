#pragma once
#include "../Core.h"
#include <GL/glew.h>

namespace qk::gfx
{
	struct QK_API VBO
	{
		GLuint m_vbo = 0;
		void upload_vertices_impl(const void* vertices, const size_t num_vertices, const size_t vertex_size, const GLenum usage);
	public:
			VBO();
			VBO(GLuint vbo);
			~VBO();
			void init();
			void bind();
			void destroy();

			operator GLuint();

			template <class vertex_t>
			void upload_vertices(const std::vector<vertex_t>& vertices, GLenum usage = GL_STATIC_DRAW)
			{
				upload_vertices_impl(vertices.data(), vertices.size(), sizeof(vertex_t), usage);
			}

	};
}

