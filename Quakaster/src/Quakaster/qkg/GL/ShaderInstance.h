#pragma once
#include "../../Core.h"
#include "import.h"
#include "Shader.h"

namespace qkg
{

	enum class gl_primitive_type
	{
		// scalars
		FLOAT,
		INT,
		BOOL,
		UINT,
		// vector types
		VEC2,
		VEC3,
		VEC4,
		
		IVEC2,
		IVEC3,
		IVEC4,

		UVEC2,
		UVEC3,
		UVEC4,

		// matrix types
		MAT2,
		MAT3,
		MAT4,
		SAMPLER_2D,
		SAMPLER_CUBE,
		SAMPLER_2D_ARRAY
	};

	class Shader;

	class QK_API ShaderInstance
	{
		GLuint m_Program = 0;
		public:
			ShaderInstance();
			~ShaderInstance();
			ShaderInstance(GLuint program);
			void set_program(GLuint program);
			GLuint program() const;
			void bind() const;
			static void unbind();
			GLuint get_uniform_location(const char* name);

			void set_uniform(GLuint location, const void* uniform, gl_primitive_type type);

	};
}