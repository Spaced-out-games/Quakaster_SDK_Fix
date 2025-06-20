#pragma once
#include "../../Core.h"
#include "import.h"
namespace qkg
{
	GLuint QK_API compile_source(const char* source, GLenum type);

	GLuint QK_API link_sources(GLuint vertex_shader, GLuint frag_shader);

}

class QK_API Shader {

};