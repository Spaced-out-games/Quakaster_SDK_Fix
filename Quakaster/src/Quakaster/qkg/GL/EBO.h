#pragma once
#include "../../Core.h"
#include <GL/glew.h> // For OpenGL types
#include <vector>
#include <iostream>
#include <cassert>

namespace qkg
{

    class QK_API EBO {
    public:


        EBO();

        EBO(const std::vector<uint32_t>& indices);

        ~EBO();

        void bind() const;

        static void unbind();

        void init(const std::vector<uint32_t>& indices);

        size_t size() const;

    private:
        size_t m_Size = 0;
        GLuint m_EBO = 0;
    };

}