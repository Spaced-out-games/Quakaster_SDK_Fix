#pragma once
#include "../../Core.h"
#include "import.h"
#include <iostream>
#include <string>


static void check_gl_error(const std::string& context) {
    GLenum err;
    if ((err = glGetError()) == GL_NO_ERROR)
    {
        std::cout << context << ": OKAY\n";
        return;
    }

    while (err != GL_NO_ERROR) {
        std::cerr << "OpenGL Error (" << context << "): " << err << std::endl;
        __debugbreak();
        err = glGetError();
    }
}
/*
void show_uniforms(GLuint programID)
{
    GLint numUniforms;
    glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &numUniforms);

    for (GLint i = 0; i < numUniforms; ++i) {
        char name[256];
        GLsizei length;
        GLint size;
        GLenum type;
        glGetActiveUniform(programID, i, sizeof(name), &length, &size, &type, name);
        printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
    }
}*/