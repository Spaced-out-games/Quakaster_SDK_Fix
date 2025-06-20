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



    void add_vec3_pointer(GLuint& index, GLsizei stride, const void* offset) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, offset);
        index++;
    }

    void add_vec2_pointer(GLuint& index, GLsizei stride, const void* offset) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride, offset);
    }

    void add_vec4_pointer(GLuint& index, GLsizei stride, const void* offset) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride, offset);
        index++;
    }

    void add_float_pointer(GLuint& index, GLsizei stride, const void* offset) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, stride, offset);
        index++;

    }

    void add_int_pointer(GLuint& index, GLsizei stride, const void* offset) {
        glEnableVertexAttribArray(index);
        glVertexAttribIPointer(index, 1, GL_INT, stride, offset);
        index++;

    }

    void add_mat4_pointer(GLuint& index, GLsizei stride, const void* offset) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride, offset);
        index++;

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride,
            static_cast<const void*>(static_cast<const char*>(offset) + sizeof(vec4)));
        index++;

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride,
            static_cast<const void*>(static_cast<const char*>(offset) + 2 * sizeof(vec4)));
        index++;

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride,
            static_cast<const void*>(static_cast<const char*>(offset) + 3 * sizeof(vec4)));
        index++;
    }





}
void print_glGenBuffersPointer()
{
    std::cout << "[CLIENT]: " << "glGenBuffers pointer: " << (void*)glGenBuffers << '\n';
}