#include "VAO.h"
#include "GL/glew.h"

namespace gfx {


	VAO::~VAO() { destroy(); }

    VAO::VAO(VAO&& other) noexcept {
        m_Handle = other.m_Handle;
        other.m_Handle = 0;
    }

    VAO& VAO::operator=(VAO&& other) noexcept {
        if (this != &other) {
            destroy();
            m_Handle = other.m_Handle;
            other.m_Handle = 0;
        }
        return *this;
    }
    void VAO::init() {
        if (m_Handle != 0) return; // prevent double init
        glGenVertexArrays(1, &m_Handle);
    }

    void VAO::bind() const {
        glBindVertexArray(m_Handle);
    }

    void VAO::unbind() {
        glBindVertexArray(0);
    }

    void VAO::destroy() {
        if (m_Handle) {
            glDeleteVertexArrays(1, &m_Handle);
            m_Handle = 0;
        }
    }

    unsigned int VAO::handle() const { return m_Handle; }


    VAO::operator unsigned int() const noexcept {
        return m_Handle;
    }

    VAO::operator bool() const noexcept {
        return m_Handle != 0;
    }

}