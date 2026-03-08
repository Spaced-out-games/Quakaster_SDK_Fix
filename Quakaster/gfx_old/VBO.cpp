#include "VBO.h"
#include "GL/glew.h"

namespace gfx {


    VBO::~VBO() { destroy(); }

    VBO::VBO(VBO&& other) noexcept {
        m_Handle = other.m_Handle;
        other.m_Handle = 0;
    }

    VBO& VBO::operator=(VBO&& other) noexcept {
        if (this != &other) {
            destroy();
            m_Handle = other.m_Handle;
            other.m_Handle = 0;
        }
        return *this;
    }
    void VBO::init() {
        if (m_Handle != 0) return; // prevent double init
        glGenBuffers(1, &m_Handle);
    }

    void VBO::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
    }

    void VBO::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VBO::destroy() {
        if (m_Handle) {
            glDeleteBuffers(1, &m_Handle);
            m_Handle = 0;
        }
    }
    void VBO::upload(const void* data, size_t size, unsigned int usage) {
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);

    }



    unsigned int VBO::handle() const { return m_Handle; }


    VBO::operator unsigned int() const noexcept {
        return m_Handle;
    }

    VBO::operator bool() const noexcept {
        return m_Handle != 0;
    }

}