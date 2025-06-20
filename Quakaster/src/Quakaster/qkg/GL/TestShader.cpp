#include "TestShader.h"


namespace qkg {

    GLuint compile_source(const char* source, GLenum type) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char log[512];
            glGetShaderInfoLog(shader, 512, nullptr, log);
            std::cerr << "[SHADER ERROR] Compilation failed: " << log << std::endl;
            glDeleteShader(shader);
            return 0;
        }
        return shader;
    }

    GLuint link_sources(GLuint vertex_shader, GLuint frag_shader) {
        GLuint program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, frag_shader);
        glLinkProgram(program);

        GLint success = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            char log[512];
            glGetProgramInfoLog(program, 512, nullptr, log);
            std::cerr << "[SHADER ERROR] Linking failed: " << log << std::endl;
            glDeleteProgram(program);
            return 0;
        }

        glDeleteShader(vertex_shader); // Optional: shaders no longer needed after link
        glDeleteShader(frag_shader);

        return program;
    }

}