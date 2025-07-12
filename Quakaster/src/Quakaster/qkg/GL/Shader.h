#pragma once
#include "../../Core.h"
#include "../../logging.h"
#include <GL/glew.h>
#include <string>
#include <unordered_map>


namespace qkg
{


	// Compiles GLSL source, given a type.
	GLuint QK_API compile_source(const char* source, const GLenum type);


	// Links a vertex shader and fragment shader, returning a shader program.
	GLuint QK_API link_sources(const std::vector<GLuint>& shaders);

	class Shader;

	// Loads shader sources from disk.
	Shader QK_API load_shader(const std::string& path, const GLenum type);

	GLuint QK_API compile_shader(Shader& shader);


	// Holds sources and GLSL shader type information. Pass into qkg::GraphicsPipeline to register the shader.
	class QK_API Shader {

		friend GLuint qkg::compile_shader(Shader& shader);
		friend class GraphicsPipeline;

		std::unordered_map<GLenum, std::string> m_Sources;

		public:
			Shader();
			inline void attach_shader(GLenum type, const std::string& source);



	};


}
