#include "VAO.h"

//for debugging
#include "gl_utils.h"

namespace qkg::vao
{

    GLuint create()
    {
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        check_gl_error("qkg::vao::create()");
        return vao;

    }

    void bind(GLuint vao)
    {
        glBindVertexArray(vao);
        check_gl_error("qkg::vao::bind(vao)");
    }

    void unbind()
    {
        bind(0);
    }

    void destroy(GLuint& vao)
    {
        if (vao != 0)
        {
            glDeleteVertexArrays(1, &vao);
            vao = 0;
        }
    }

}