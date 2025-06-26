#include "ShaderInstance.h"



namespace qkg
{
	ShaderInstance::ShaderInstance(): m_Program(0)
	{

	}
	
	ShaderInstance::~ShaderInstance()
	{
		if (m_Program) glDeleteProgram(m_Program);
	}

	ShaderInstance::ShaderInstance(GLuint program): m_Program(program)
	{

	}


	void ShaderInstance::bind() const
	{
		glUseProgram(m_Program);
	}
	void ShaderInstance::unbind()
	{
		glUseProgram(0);
	}

	void ShaderInstance::set_program(GLuint program)
	{
		m_Program = program;
	}
	inline GLuint ShaderInstance::program() const
	{
		return m_Program;
	}

    GLuint ShaderInstance::get_uniform_location(const char* name)
    {
        return glGetUniformLocation(m_Program, name);
    }

    inline void ShaderInstance::set_uniform(GLuint location, const void* uniform, qkg::gl_primitive_type type)
    {
        switch (type)
        {
        case qkg::gl_primitive_type::FLOAT:
            glUniform1f(location, *reinterpret_cast<const GLfloat*>(uniform));
            break;
        case qkg::gl_primitive_type::INT:
        case qkg::gl_primitive_type::BOOL:
            glUniform1i(location, *reinterpret_cast<const GLint*>(uniform));
            break;
        case qkg::gl_primitive_type::UINT:
            glUniform1ui(location, *reinterpret_cast<const GLuint*>(uniform));
            break;

        case qkg::gl_primitive_type::VEC2:
            glUniform2fv(location, 1, reinterpret_cast<const GLfloat*>(uniform));
            break;
        case qkg::gl_primitive_type::VEC3:
            glUniform3fv(location, 1, reinterpret_cast<const GLfloat*>(uniform));
            break;
        case qkg::gl_primitive_type::VEC4:
            glUniform4fv(location, 1, reinterpret_cast<const GLfloat*>(uniform));
            break;

        case qkg::gl_primitive_type::IVEC2:
            glUniform2iv(location, 1, reinterpret_cast<const GLint*>(uniform));
            break;
        case qkg::gl_primitive_type::IVEC3:
            glUniform3iv(location, 1, reinterpret_cast<const GLint*>(uniform));
            break;
        case qkg::gl_primitive_type::IVEC4:
            glUniform4iv(location, 1, reinterpret_cast<const GLint*>(uniform));
            break;

        case qkg::gl_primitive_type::UVEC2:
            glUniform2uiv(location, 1, reinterpret_cast<const GLuint*>(uniform));
            break;
        case qkg::gl_primitive_type::UVEC3:
            glUniform3uiv(location, 1, reinterpret_cast<const GLuint*>(uniform));
            break;
        case qkg::gl_primitive_type::UVEC4:
            glUniform4uiv(location, 1, reinterpret_cast<const GLuint*>(uniform));
            break;

        case qkg::gl_primitive_type::MAT2:
            glUniformMatrix2fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(uniform));
            break;
        case qkg::gl_primitive_type::MAT3:
            glUniformMatrix3fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(uniform));
            break;
        case qkg::gl_primitive_type::MAT4:
            glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(uniform));
            break;

        case qkg::gl_primitive_type::SAMPLER_2D:
        case qkg::gl_primitive_type::SAMPLER_CUBE:
        case qkg::gl_primitive_type::SAMPLER_2D_ARRAY:
            glUniform1i(location, *reinterpret_cast<const GLint*>(uniform)); // set the texture unit
            break;

        default:
            // Optionally log an error or assert
            break;
        }
    }
}