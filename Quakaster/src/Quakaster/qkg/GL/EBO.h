#pragma once
#include "../../Core.h"
#include "import.h"
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

        uint32_t size() const;

    private:
        GLuint m_EBO = 0;
        uint32_t m_Size = 0;
    };

}