#pragma once
#include "../../Core.h"
#include <GL/glew.h>



namespace qkg
{
    template<typename T>
    class MeshConfiguration;

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

        void set_ID(GLuint new_vao);
    private:
        template<class vertex_t>
        friend class MeshConfiguration;

        GLuint m_VAO = 0;


    };

}