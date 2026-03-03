#include "Shader.h"
#include "GL/glew.h"
#include "spdlog/spdlog.h"

namespace gfx {

	unsigned int Shader::compile() const{
        GLuint shader = glCreateShader(m_Type);
        const char* src = m_Source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char error[512];
            glGetShaderInfoLog(shader, 512, nullptr, error);

            spdlog::error("Shader compile error: {}", error);

        }

        return shader;
	}

    Shader::Shader(const Source& source, Type type) {
        m_Source = source;
        m_Type = type;
    }



}