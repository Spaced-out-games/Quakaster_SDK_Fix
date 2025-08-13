#include "MeshConfiguration.h"

namespace qkg {



    

    void add_vec3_pointer(GLuint& index, GLsizei stride, size_t offset)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
    }

    void add_vec2_pointer(GLuint& index, GLsizei stride, size_t offset)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride, (void*)offset);
    }

    void add_vec4_pointer(GLuint& index, GLsizei stride, size_t offset)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride, (void*)offset);
        index++;
    }

    void add_float_pointer(GLuint& index, GLsizei stride, size_t offset)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, stride, (void*)offset);
        index++;
    }

    void add_quat_pointer(GLuint& index, GLsizei stride, size_t offset)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride, (void*)offset);
        index++;
    }


    void add_int_pointer(GLuint& index, GLsizei stride, size_t offset) {
        glEnableVertexAttribArray(index);
        glVertexAttribIPointer(index, 1, GL_INT, stride, (void*)offset);
        index++;

    }

    void add_uint_pointer(GLuint& index, GLsizei stride, size_t offset)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribIPointer(index, 1, GL_UNSIGNED_INT, stride, (void*)offset);
        index++;
    }


    void add_mat4_pointer(GLuint& index, GLsizei stride, size_t offset) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
        index++;

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride, (const void*)(offset + sizeof(qk::vec4)));
        index++;

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride, (const void*)(offset + 2 * sizeof(qk::vec4)));
        index++;

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride, (const void*)(offset + 3 * sizeof(qk::vec4)));
        index++;
    }

}