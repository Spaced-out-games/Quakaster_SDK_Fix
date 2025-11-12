#include "Uniform.h"
#include "../qkmath/qkmath.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>


namespace qk::gfx
{
	GLuint Uniform::get_uniform_location(std::string name, GLuint program)
	{
		return glGetUniformLocation(program, name.c_str());
	}

	GLuint Uniform::get_program() const
	{
		return m_Program;
	}
	GLuint Uniform::get_location() const
	{
		return m_Location;
	}
	Uniform::operator bool() const
	{
		return m_Data;
	}

	Uniform::~Uniform()
	{
		if (m_Destructor) m_Destructor(m_Data);
	}

    void Uniform::update()
    {
        if (!m_Data) return;
        glUseProgram(m_Program);

        if (is<float>())
        {
            glUniform1f(m_Location, *reinterpret_cast<float*>(m_Data));
        }
        else if (is<int>())
        {
            glUniform1i(m_Location, *reinterpret_cast<int*>(m_Data));
        }
        else if (is<qk::vec3>())
        {
            qk::vec3* p = reinterpret_cast<qk::vec3*>(m_Data);
            glUniform3fv(m_Location, 1, glm::value_ptr(*p));
        }
        else if (is<qk::mat4>())
        {
            qk::mat4* p = reinterpret_cast<qk::mat4*>(m_Data);
            glUniformMatrix4fv(m_Location, 1, GL_FALSE, glm::value_ptr(*p));
        }
        else if (is<qk::quat>())
        {
            qk::quat* p = reinterpret_cast<qk::quat*>(m_Data);
            glUniform4fv(m_Location, 1, glm::value_ptr(*p));
        }
        else
        {
            __debugbreak();
            assert(false && "Unsupported uniform type");
        }
    }


}