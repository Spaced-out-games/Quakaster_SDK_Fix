#include "EBO.h"

namespace qkg::ebo
{


    EBO create()
    {
        EBO ebo;
        glGenBuffers(1, &ebo);
        return ebo;
    }

    void bind(EBO ebo)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    }

    inline void unbind()
    {
        bind(0);
    }

    void destroy(EBO& ebo)
    {
        if (ebo != 0)
        {
            glDeleteBuffers(1, &ebo);
            // set it to a valid state
            ebo = 0;
        }
    }

    void upload_indices(const std::vector<uint32_t>& indices, GLenum usage)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), usage);
    }


}



/*
namespace qkg
{
    EBO::EBO() {}

    EBO::EBO(const std::vector<uint32_t>& indices) {
        init(indices);
    }

    EBO::~EBO() {
        glDeleteBuffers(1, &m_EBO); // Cleanup
    }

    void EBO::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); // Bind the EBO

    }

    void EBO::unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind any EBO

    }

    void EBO::init(const std::vector<uint32_t>& indices) {
        glGenBuffers(1, &m_EBO); // Generate an EBO

        bind(); // Bind the EBO


        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
        m_Size = indices.size(); // Store the index count

    }

    size_t EBO::size() const {
        return m_Size; // Return the stored index count
    }

}
*/