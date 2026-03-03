#pragma once
#include "../core.h"
#include "glm/mat4x4.hpp"


namespace qk::math {

	class QK_API CCamera {
		float m_FovRadians = glm::radians(90.0f);
		float m_Near = 0.001f;
		float m_Far = 1000.0f;
		float m_AspectRatio = 16.0f / 9.0f;

		public:
		glm::mat4 projection() const;
		CCamera(float fov_degrees, float near, float far, float aspect_ratio);

		void set_fov(float fov_degrees);
		float fov() const;

		void set_near(float near);
		float near() const;

		void set_far(float far);
		float far() const;

		void set_aspect(float new_aspect);
		float aspect() const;

	};

}