#pragma once
#include "../../Core.h"
#include "../../qkmath/qkmath.h"
#include "gl_utils.h"
#include "import.h"
#include <iostream>
#include <vector>
#include <cassert>

namespace qkg
{
    class QK_API VBO {

        

    public:

        VBO();
        ~VBO();

        void init_impl(const void* vertices, const size_t num_vertices, const size_t vertex_size);

        

        void bind() const;

        static void unbind();

        GLsizei size() const;


        template <typename vertex_t = default_vertex_t>
        VBO(const std::vector<vertex_t>& vertices) {
            init<vertex_t>(vertices);
        }

        

        // Helper function to respect DLL boundaries. The problem was that it couldn't export symbols to the client, since
        // templates at the end of the day are inlined code. Solution? Make a generic type-erased function, template-wrap.
        template <typename vertex_t>

        void init(const std::vector<vertex_t>& vertices) {
            init_impl(vertices.data(), vertices.size(), sizeof(vertex_t));
        }







    private:
        GLsizei m_Size = 0;
        GLuint vboID = 0x0; // The ID of the VBO


    };

    void QK_API add_int_pointer(GLuint& index, GLsizei stride, const void* offset);
    void QK_API add_float_pointer(GLuint& index, GLsizei stride, const void* offset);
    void QK_API add_vec2_pointer(GLuint& index, GLsizei stride, const void* offset);
    void QK_API add_vec3_pointer(GLuint& index, GLsizei stride, const void* offset);
    void QK_API add_vec4_pointer(GLuint& index, GLsizei stride, const void* offset);
    void QK_API add_mat4_pointer(GLuint& index, GLsizei stride, const void* offset);

}
void QK_API print_glGenBuffersPointer();
