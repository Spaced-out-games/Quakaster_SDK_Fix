#pragma once
#include "../../Core.h"
#include "../../qkmath/qkmath.h"
#include "gl_utils.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <cassert>

using VBO = GLuint;

namespace qkg::vbo
{
    VBO QK_API create();

    void QK_API bind(VBO vbo);

    inline void unbind();

    void QK_API destroy(VBO& vbo);

    void QK_API upload_vertices_impl(VBO vbo, const void* vertices, const size_t num_vertices, const size_t vertex_size, GLenum usage = GL_STATIC_DRAW);

    template <class vertex_t>
    void upload_vertices(VBO vbo, const std::vector<vertex_t>& vertices, GLenum usage = GL_STATIC_DRAW)
    {
        upload_vertices_impl(vbo, vertices.data(), vertices.size(), sizeof(vertex_t), usage);
    }

}




void QK_API print_glGenBuffersPointer();
