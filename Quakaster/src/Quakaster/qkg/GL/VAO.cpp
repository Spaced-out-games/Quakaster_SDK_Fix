#include "VAO.h"

namespace qkg
{
    VAO::VAO() {}

    VAO::~VAO() {
        if (m_VAO != 0) {
            glDeleteVertexArrays(1, &m_VAO); // Cleanup
        }
    }

    void VAO::init()
    {
        glGenVertexArrays(1, &m_VAO); // Generate a VAO
        check_gl_error("qkg::VAO::init()");
    }

    void VAO::bind() const {
        glBindVertexArray(m_VAO); // Bind the VAO
        check_gl_error("qkg::VAO::bind()");

    }

    void VAO::unbind() {
        glBindVertexArray(0); // Unbind any VAO
        check_gl_error("qkg::VAO::unbind()");

    }

    VAO::VAO(VAO&& other) noexcept : m_VAO(other.m_VAO) {
        other.m_VAO = 0; // Null out other's handle to avoid deletion
    }

    VAO& VAO::operator=(VAO&& other) noexcept {
        if (this != &other) {
            // Delete current VAO if any
            if (m_VAO != 0) {
                glDeleteVertexArrays(1, &m_VAO);
            }
            m_VAO = other.m_VAO;
            other.m_VAO = 0; // Null out other's handle
        }
        return *this;
    }

}