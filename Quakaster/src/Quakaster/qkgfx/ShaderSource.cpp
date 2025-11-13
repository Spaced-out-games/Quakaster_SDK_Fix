#include "ShaderSource.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace qk::gfx
{
    GLuint compile_source(const char* source, GLenum type, Error* out) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (out)
        {
            *out = get_error(shader, success);
        }
        return shader;
    }

    GLuint link_sources(const std::vector<GLuint>& shaders, Error* out) {
        GLuint program = glCreateProgram();
        for (const GLuint& shader : shaders)
        {
            glAttachShader(program, shader);
        }
        glLinkProgram(program);

        GLint success = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (out)
        {
            *out = get_error(program, success);
        }

        for (const GLuint& shader : shaders)
        {
            glDeleteShader(shader);

        }

        return program;
    }
    void use_shader(GLuint shader)
    {
        glUseProgram(shader);
    }
    void lazy_draw(GLsizei count)
    {
        //glDisable(GL_CULL_FACE);
        

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);

    }
    Error get_error(GLuint shader, bool success)
    {
        GLint currentProgram = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

        if (success) return Error{ Error_t::NONE, nullptr };
        char* log = new char[512];
        glGetShaderInfoLog(currentProgram, 512, nullptr, log);
        glDeleteShader(shader);
        return Error{ Error_t::GFX_SHADER_COMPILE_ERROR, log };
    }

}