#pragma once

#include <glm/gtc/quaternion.hpp> // basic quat
#include <glm/gtx/quaternion.hpp> // extended utilities (optional)

namespace qk
{
    using quat = glm::quat;

    using glm::angleAxis;      // create quat from angle + axis
    using glm::conjugate;      // conjugate of quaternion
    using glm::cross;          // cross product (useful sometimes)
    using glm::dot;            // dot product
    using glm::inverse;        // inverse quaternion
    using glm::length;         // length of quaternion
    using glm::normalize;      // normalize quat
    using glm::slerp;          // spherical linear interpolation
    using glm::toMat3;         // convert quat to mat3
    using glm::toMat4;         // convert quat to mat4
    using glm::rotation;       // rotation between two vectors
    using glm::mix;            // linear interpolation
    // ... add others as needed

}