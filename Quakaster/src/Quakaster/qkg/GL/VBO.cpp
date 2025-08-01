#include "VBO.h"


namespace qkg::vbo
{
    VBO create()
    {
        VBO result = 0;
        check_gl_error("qkg::VBO::init<T>() begin");
        glGenBuffers(1, &result);
        check_gl_error("qkg::VBO::init<T>() end");
        return result;
    }

    void bind(VBO vbo)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        check_gl_error("qkg::vbo::bind()");
    }

    void unbind()
    {
        bind(0);
    }

    void destroy(VBO& vbo)
    {
        if (vbo != 0)
        {
            glDeleteBuffers(1, &vbo);
            vbo = 0; // mark deleted
        }
        check_gl_error("qkg::vbo::destroy()");
    }

    void upload_vertices_impl(VBO vbo, const void* vertices, const size_t num_vertices, const size_t vertex_size, GLenum usage)
    {
        bind(vbo);
        glBufferData(GL_ARRAY_BUFFER, num_vertices * vertex_size, vertices, usage);

    }
}


void print_glGenBuffersPointer()
{
    std::cout << "[CLIENT]: " << "glGenBuffers pointer: " << (void*)glGenBuffers << '\n';
}