#include "Shader.h"




namespace qkg
{

    GLuint compile_source(const char* source, GLenum type) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char log[512];
            glGetShaderInfoLog(shader, 512, nullptr, log);
            std::cerr << "[SHADER ERROR] Compilation failed ("
                << (type == GL_VERTEX_SHADER ? "VERTEX" :
                    type == GL_FRAGMENT_SHADER ? "FRAGMENT" :
                    type == GL_GEOMETRY_SHADER ? "GEOMETRY" : "OTHER")
                << "): " << log << std::endl;
            glDeleteShader(shader);
            return 0;
        }
        return shader;
    }
    GLuint link_sources(const std::vector<GLuint>& shaders) {
        GLuint program = glCreateProgram();
        for (const GLuint& shader : shaders)
        {
            glAttachShader(program, shader);
        }
        glLinkProgram(program);

        GLint success = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            char log[512];
            glGetProgramInfoLog(program, 512, nullptr, log);
            std::cerr << "[SHADER ERROR] Linking failed: " << log << std::endl;
            glDeleteProgram(program);
            return 0;
        }

        for (const GLuint& shader : shaders)
        {
            glDeleteShader(shader);

        }

        return program;
    }

    Shader load_shader(const std::string& path, const GLenum type)
    {
        return Shader();
    }

    GLuint compile_shader(Shader& shader)
    {
        // compile each sub-shader
        std::vector<GLuint> compiled_shaders{};


        // we only need one per hash map bucket
        compiled_shaders.reserve(shader.m_Sources.size());


        // go through each subshader, compile, save the program code
        for (const auto& [channel, source] : shader.m_Sources)
        {
            compiled_shaders.push_back(compile_source(source.c_str(), channel));
        }

        // link all of them, save the code

        return link_sources(compiled_shaders);


    }



    Shader::Shader()  {}

    inline void Shader::attach_shader(GLenum type, const std::string& source)
    {
        if (m_Sources.find(type) == m_Sources.end())
        {
            m_Sources[type] = source;
        }
    }


    

    

}
