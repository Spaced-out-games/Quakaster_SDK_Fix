// vec3.h
#pragma once
#include <glm/vec4.hpp>       // for glm::vec3
#include <glm/geometric.hpp>  // for dot, cross, length, normalize, etc.

namespace qk {
    using vec4 = glm::vec4;
    using glm::dot;
    using glm::cross;
    using glm::length;
    using glm::normalize;
}
