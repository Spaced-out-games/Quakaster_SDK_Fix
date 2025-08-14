#pragma once
#include "vec3.h"
#include "quaternion.h"
#include "mat4.h"

namespace qk
{
    class CTransform
    {
        vec3 m_Position;
        quat m_Rotation;

    public:
        CTransform() = default;
        inline void rotate_local(quat delta) { m_Rotation *= delta; }
        inline void rotate_world(quat delta) { m_Rotation = delta * m_Rotation; }

        inline void translate_world(vec3 delta) { m_Position += delta; }
        inline void translate_local(vec3 delta) { m_Position += m_Rotation * delta; }

        inline mat4 as_matrix() const
        {
            // Start with rotation
            mat4 m = glm::toMat4(m_Rotation);

            // Apply translation directly
            m[3] = glm::vec4(m_Position, 1.0f); // sets the fourth column for translation

            return m;
        }

        inline vec3 get_forward_vector() const
        {
            return m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f);
        }

        inline vec3 get_right_vector() const
        {
            return m_Rotation * glm::vec3(1.0f, 0.0f, 0.0f);
        }

        inline vec3 get_up_vector() const
        {
            return m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f);
        }

    };
}