#include "Camera.h"



namespace qk {
	Camera::Camera(float FOV, float Aspect, float Near, float Far) :
		m_Fov(FOV),
		m_AspectRatio(Aspect),
		m_Near(Near),
		m_Far(Far)
	{

	}



	Camera::Camera(): m_Fov(120.0f), m_AspectRatio(16.0f/9.0f), m_Near(0.0001f), m_Far(1000.0f)
	{

	}

	mat4 Camera::projection()
	{
		return glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_Near, m_Far);
	}
	void Camera::set_fov(float new_fov)
	{
		m_Fov = new_fov;
	}
	void Camera::set_near(float new_near)
	{
		m_Near = new_near;
	}
	void Camera::set_far(float new_far)
	{
		m_Far = new_far;
	}
	void Camera::set_aspect(float new_aspect)
	{
		m_AspectRatio = new_aspect;
	}

}