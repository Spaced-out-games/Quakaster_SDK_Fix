#pragma once
#include "../../Core.h"
#include <GL/glew.h>



namespace qkg::vao
{
    GLuint QK_API create();

    void QK_API bind(GLuint vao);

    inline void unbind();

    void QK_API destroy(GLuint& vao);

}