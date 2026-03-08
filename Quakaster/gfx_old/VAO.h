#pragma once
#include "../core.h"

namespace gfx {
    class QK_API VAO {
        unsigned int m_Handle = 0;
        VAO(VAO&& other) noexcept;

        VAO& operator=(VAO&& other) noexcept;
    public:
        VAO() = default;
        ~VAO();

        VAO(const VAO&) = delete;
        VAO& operator=(const VAO&) = delete;



        void init();

        void bind() const;

        static void unbind();

        void destroy();

        unsigned int handle() const;

        operator unsigned int() const noexcept;

        explicit operator bool() const noexcept;
    };

}
