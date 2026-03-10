#pragma once
#include <stdint.h>
#include "../../core.h"
namespace qk {
    struct QK_API ScopeTimer {
        uint64_t* m_Target = nullptr;
        uint64_t m_StartTime = 0;

        explicit ScopeTimer(uint64_t* target_out);

        ~ScopeTimer();

        // non-copyable
        ScopeTimer(const ScopeTimer&) = delete;
        ScopeTimer& operator=(const ScopeTimer&) = delete;

        ScopeTimer(ScopeTimer&& other) noexcept;
        ScopeTimer& operator=(ScopeTimer&& other) noexcept;
    };
}