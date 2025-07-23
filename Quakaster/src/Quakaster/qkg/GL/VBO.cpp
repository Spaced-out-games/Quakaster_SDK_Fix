#include "VBO.h"


namespace qkg
{

    VBO::VBO() {
        //check_gl_error("qkg::VBO()");

    }

    VBO::~VBO() {
        if (vboID != 0) {
            glDeleteBuffers(1, &vboID); // Cleanup

        }
        check_gl_error("qkg::~VBO()");

    }

    void VBO::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind the VBO
        check_gl_error("qkg::VBO::bind()");
    }

    void VBO::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        check_gl_error("qkg::VBO::unbind()");

    }

    GLsizei VBO::size() const { return m_Size; }

    
    void VBO::init_impl(const void* vertices, const size_t num_vertices, const size_t vertex_size)
    {
        m_Size = (GLsizei)num_vertices;
        check_gl_error("qkg::VBO::init<T>() begin");
        glGenBuffers(1, &vboID);
        check_gl_error("qkg::VBO::init<T>()");
        bind();
        glBufferData(GL_ARRAY_BUFFER, num_vertices * vertex_size, vertices, GL_STATIC_DRAW);

    }








}
void print_glGenBuffersPointer()
{
    std::cout << "[CLIENT]: " << "glGenBuffers pointer: " << (void*)glGenBuffers << '\n';
}