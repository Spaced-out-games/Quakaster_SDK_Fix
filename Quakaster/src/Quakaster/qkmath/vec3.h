// vec3.h
#pragma once
#include <glm/vec3.hpp>       // for glm::vec3
#include <glm/geometric.hpp>  // for dot, cross, length, normalize, etc.

namespace qk {
    using vec3 = glm::vec3;
    using glm::dot;
    using glm::cross;
    using glm::length;
    using glm::normalize;
}
