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

}