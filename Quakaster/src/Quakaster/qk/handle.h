#pragma once
#include <stdint.h>

namespace qk
{
    template <typename T>
    struct Handle {
        uintptr_t m_hdl = 0;
        static_assert(
            std::is_pointer_v<T> || (std::is_integral_v<T> && sizeof(T) <= sizeof(uintptr_t)),
            "qk::Handle<T> must be a pointer or an integral type no larger than uintptr_t"
            );
    protected:
        explicit Handle(T value) noexcept {
            if constexpr (std::is_pointer_v<T>) {
                m_hdl = reinterpret_cast<uintptr_t>(value);
            }
            else {
                m_hdl = static_cast<uintptr_t>(value);
            }
        }

    public:
        Handle() = default;
        Handle(const Handle&) = default;
        Handle& operator=(const Handle&) = default;

        operator T() const noexcept { return reinterpret_cast<T>(m_hdl); }

        template <typename U>
        friend Handle<U> make_Handle(U);

        Handle& operator=(std::nullptr_t) noexcept {
            if constexpr (std::is_pointer_v<T>) {
                m_hdl = reinterpret_cast<uintptr_t>(nullptr);
            }
            else {
                m_hdl = uintptr_t(0);
            }
            return *this;
        }
    };

    // Factory helper
    template <typename T>
    Handle<T> make_Handle(T value) {
        return Handle<T>(value);
    }
}
