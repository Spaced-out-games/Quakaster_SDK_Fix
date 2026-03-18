#include "ShaderProgram.h"
#include "spdlog/spdlog.h"
#include "GL/glew.h"


namespace qk::gfx {

	bool ShaderProgram::init(const Handle frag, const Handle vert) {

        if(m_Handle) return false;

        m_Handle = glCreateProgram();
        glAttachShader(m_Handle, frag);
        glAttachShader(m_Handle, vert);
        glLinkProgram(m_Handle);

        int success;
        glGetProgramiv(m_Handle, GL_LINK_STATUS, &success);
        if (!success) {
            char error[512];
            glGetProgramInfoLog(m_Handle, 512, nullptr, error);
            spdlog::error("Program link error: {}", error);
            return false;
        }

        glDeleteShader(vert);
        glDeleteShader(frag);

        return true;

	}

    void ShaderProgram::bind() {
        glUseProgram(m_Handle);
    }

    void ShaderProgram::unbind() {
        glUseProgram(0);
    }

    Handle ShaderProgram::handle() const {
        return m_Handle;
    }


}