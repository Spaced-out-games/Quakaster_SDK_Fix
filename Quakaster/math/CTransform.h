#pragma once
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/quaternion.hpp"
#include "../core.h"



namespace qk::math {

	class QK_API CTransform {
		glm::vec3 m_Position = {};
		glm::quat m_Rotation;
		glm::vec3 m_Scale = { 1.0, 1.0,1.0 };

		public:

			glm::mat4 operator()() const {
				return toMat4();
			}

			glm::mat4 toMat4() const {
				glm::mat4 T = glm::translate(glm::mat4(1.0f), m_Position);
				glm::mat4 R = glm::mat4_cast(m_Rotation);
				glm::mat4 S = glm::scale(glm::mat4(1.0f), m_Scale);
				return T * R * S;
			}

			void translate(glm::vec3 delta) {
				m_Position += delta;
			}

			void scale(glm::vec3 delta) {
				m_Scale *= delta;
			}

			void rotate(glm::quat delta) {
				m_Rotation = glm::normalize(m_Rotation * delta);
			}

			void rotate_x(float yaw_radians) {
				glm::quat delta = glm::angleAxis(yaw_radians, glm::vec3(1, 0, 0));
				m_Rotation = glm::normalize(delta * m_Rotation);
			}

			void rotate_y(float pitch_radians) {
				glm::quat delta = glm::angleAxis(pitch_radians, glm::vec3(0, 1, 0));
				m_Rotation = glm::normalize(delta * m_Rotation);
			}

			void rotate_z(float roll_radians) {
				glm::quat delta = glm::angleAxis(roll_radians, glm::vec3(0, 0, 1));
				m_Rotation = glm::normalize(delta * m_Rotation);
			}

			void decompose(const glm::mat4& m) {
				glm::vec3 skew;
				glm::vec4 perspective;
				glm::decompose(m, m_Scale, m_Rotation, m_Position, skew, perspective);
				m_Rotation = glm::normalize(m_Rotation);
			}

			glm::mat4 toWorld(const glm::mat4& parentWorld) const {
				return parentWorld * toMat4();
			}

			glm::mat4 toWorld(const CTransform& parent) const {
				return parent.toMat4() * toMat4();
			}

			void fromWorld(const glm::mat4& parentWorld, const glm::mat4& world) {
				glm::mat4 local = glm::inverse(parentWorld) * world;
				decompose(local);
			}

			void fromWorld(const CTransform& parent, const glm::mat4& world) {
				fromWorld(parent.toMat4(), world);
			}

			glm::mat4 toLocal(const glm::mat4& parentWorld) const {
				return glm::inverse(parentWorld) * toMat4();
			}

			glm::mat4 toLocal(const CTransform& parent) const {
				return glm::inverse(parent.toMat4()) * toMat4();
			}




	};

}