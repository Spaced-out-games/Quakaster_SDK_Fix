#include "Camera.h"

namespace qk {
	Camera::Camera(float FOV, float Aspect, float Near, float Far) :
		m_Fov(FOV),
		m_AspectRatio(Aspect),
		m_Near(Near),
		m_Far(Far)
	{

	}

	Camera::Camera(float* FOV_ptr, float* Aspect_ptr, float* Near_ptr, float* Far_ptr) :
		m_Fov(FOV_ptr),
		m_AspectRatio(Aspect_ptr),
		m_Near(Near_ptr),
		m_Far(Far_ptr)
	{

	}

	mat4 Camera::projection()
	{
		return glm::perspective(glm::radians(m_Fov.get()), m_AspectRatio.get(), m_Near.get(), m_Far.get());
	}
}