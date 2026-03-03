#pragma once
#include "../core.h"

namespace gfx {

    class QK_API VBO {
        unsigned int m_Handle = 0;

    public:
        VBO() = default;
        ~VBO();

        VBO(const VBO&) = delete;
        VBO& operator=(const VBO&) = delete;

        VBO(VBO&& other) noexcept;

        VBO& operator=(VBO&& other) noexcept;

        void init();

        void bind() const;

        static void unbind();

        void destroy();

        unsigned int handle() const;

        void upload(const void* data, size_t size, unsigned int usage);


        operator unsigned int() const noexcept;

        explicit operator bool() const noexcept;


    };
}