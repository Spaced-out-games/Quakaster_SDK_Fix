#include "GraphicsPrimitiveService.h"
#include "GL/glew.h"
#include "spdlog/spdlog.h"

namespace gfx {

	unsigned int GraphicsPrimitiveService::VBO_ctor_impl() {
		unsigned int vbo;
		glGenBuffers(1, &vbo);
		return vbo;
	}

    void GraphicsPrimitiveService::VBO_dtor_impl(unsigned int target) {
        glDeleteBuffers(1, &target);
    }


	void GraphicsPrimitiveService::VBO_bind_impl(unsigned int target) {
		glBindBuffer(GL_ARRAY_BUFFER, target);
	}

	void GraphicsPrimitiveService::VBO_upload_impl(const void* data, ptrdiff_t size, GLenum usage) {
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	}

    unsigned int GraphicsPrimitiveService::VAO_ctor_impl() {
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		return vao;
	}

    void GraphicsPrimitiveService::VAO_dtor_impl(unsigned int target) {
        glDeleteVertexArrays(1, &target);
    }


    void GraphicsPrimitiveService::VAO_bind_impl(unsigned int vao) {
        glBindVertexArray(vao);
    }

    unsigned int GraphicsPrimitiveService::shader_compile_impl(unsigned int type, const char* src) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);

            spdlog::error("Shader compile error: {}", infoLog);

        }

        return shader;
    }

    unsigned int GraphicsPrimitiveService::shader_program_ctor_impl(const char* vertSrc, const char* fragSrc) {
        GLuint vert = shader_compile_impl(GL_VERTEX_SHADER, vertSrc);
        GLuint frag = shader_compile_impl(GL_FRAGMENT_SHADER, fragSrc);

        GLuint program = glCreateProgram();
        glAttachShader(program, vert);
        glAttachShader(program, frag);
        glLinkProgram(program);

        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            spdlog::error("Program link error: {}", infoLog);

        }

        glDeleteShader(vert);
        glDeleteShader(frag);

        return program;
    }

    void GraphicsPrimitiveService::shader_program_bind_impl(unsigned int program) {
        glUseProgram(program);

    }
    void GraphicsPrimitiveService::drawArrays(unsigned int mode, int first, int count) {
        glDrawArrays(mode, first, (GLsizei)count);

    }


}