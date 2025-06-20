#pragma once
#include "../../Core.h"
#include "import.h"
#include "gl_utils.h"
namespace qkg
{
    class QK_API VAO {
    public:

        // Doesn't call init();
        VAO();

        // Destructor to clean up VAO
        ~VAO();

        // Move constructor
        VAO(VAO&& other) noexcept;

        // Move assignment
        VAO& operator=(VAO&& other) noexcept;

        // Delete copy constructor and copy assignment to avoid double deletes
        VAO(const VAO&) = delete;
        VAO& operator=(const VAO&) = delete;

        void init();

        void bind() const;

        static void unbind();


    private:
        GLuint m_VAO = 0;


    };

}