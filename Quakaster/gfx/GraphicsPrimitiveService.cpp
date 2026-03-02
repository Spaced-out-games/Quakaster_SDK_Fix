#include "GraphicsPrimitiveService.h"
#include "GL/glew.h"
#include "spdlog/spdlog.h"

namespace gfx {

	unsigned int make_vertexBuffer_impl() {
		unsigned int vbo;
		glGenBuffers(1, &vbo);
		return vbo;
	}

	void bind_vertexBuffer_impl(unsigned int target) {
		glBindBuffer(GL_ARRAY_BUFFER, target);
	}

	void upload_vertexBuffer_impl(const void* data, ptrdiff_t size, GLenum usage) {
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	}

    unsigned int generate_vao() {
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		return vao;
	}
    void bind_vao(unsigned int vao) {
        glBindVertexArray(vao);
    }

    unsigned int compile_shader(unsigned int type, const char* src) {
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

    unsigned int create_shader_program(const char* vertSrc, const char* fragSrc) {
        GLuint vert = compile_shader(GL_VERTEX_SHADER, vertSrc);
        GLuint frag = compile_shader(GL_FRAGMENT_SHADER, fragSrc);

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

    void bind_shader_program(unsigned int program) {
        glUseProgram(program);

    }
    void drawArrays(unsigned int mode, int first, int count) {
        glDrawArrays(mode, first, (GLsizei)count);

    }


}