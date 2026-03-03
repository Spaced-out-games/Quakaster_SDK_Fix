#include "ShaderProgram.h"
#include "spdlog/spdlog.h"
#include "GL/glew.h"


namespace gfx {

	bool ShaderProgram::init(const Shader& frag, const Shader& vert) {

        if(m_Handle) return false;
        
		unsigned int frag_shader = frag.compile();
		unsigned int vert_shader = vert.compile();

        m_Handle = glCreateProgram();
        glAttachShader(m_Handle, vert_shader);
        glAttachShader(m_Handle, frag_shader);
        glLinkProgram(m_Handle);

        int success;
        glGetProgramiv(m_Handle, GL_LINK_STATUS, &success);
        if (!success) {
            char error[512];
            glGetProgramInfoLog(m_Handle, 512, nullptr, error);
            spdlog::error("Program link error: {}", error);

        }

        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);

        return true;

	}

    void ShaderProgram::bind() {
        glUseProgram(m_Handle);
    }

    void ShaderProgram::unbind() {
        glUseProgram(0);
    }

}