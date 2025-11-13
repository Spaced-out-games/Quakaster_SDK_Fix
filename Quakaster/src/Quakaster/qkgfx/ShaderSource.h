#pragma once
#include "../Core.h"
#include "Error.h"
#include <string>
#include <GL/glew.h>

namespace qk::gfx
{
	GLuint QK_API compile_source(const char* source, const GLenum type, Error* out = nullptr);
	GLuint QK_API link_sources(const std::vector<GLuint>& shaders, Error* out = nullptr);
	void QK_API use_shader(GLuint shader);
	void QK_API lazy_draw(GLsizei count);
	Error QK_API get_error(GLuint shader, bool success);
}

