#pragma once
#include "../../Core.h"
#include "import.h"
#include "Shader.h"

namespace qkg
{

	class Shader;

	class QK_API ShaderInstance
	{
		GLuint m_Program = 0;
		public:
			ShaderInstance();
			~ShaderInstance();
			ShaderInstance(GLuint program);
			inline void set_program(GLuint program);

			inline void bind() const;
			static void unbind();

	};
}