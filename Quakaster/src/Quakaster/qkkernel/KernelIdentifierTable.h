#pragma once
#include "../Core.h"
#include <entt/core/hashed_string.hpp>
#include <string>

namespace qk::kernel::id {

    // Inserts or returns existing hash for a string
    QK_API entt::id_type add(const std::string& identifier);

    // Removes identifier from the table (optional)
    QK_API void remove(entt::id_type hash);

    // Const access by ID; returns "<unknown>" if not found
    QK_API const std::string& name(entt::id_type hash);

    // gets the LUT
    QK_API const std::unordered_map<entt::id_type, std::string>& lut();
}