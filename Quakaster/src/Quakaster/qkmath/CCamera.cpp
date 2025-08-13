#include "CCamera.h"



namespace qk {
	CCamera::CCamera(float FOV, float Aspect, float Near, float Far) :
		m_Fov(FOV),
		m_AspectRatio(Aspect),
		m_Near(Near),
		m_Far(Far)
	{

	}
	CCamera::CCamera(float* FOV_ptr, float* Aspect_ptr, float* Near_ptr, float* Far_ptr) :
		m_Fov(FOV_ptr),
		m_AspectRatio(Aspect_ptr),
		m_Near(Near_ptr),
		m_Far(Far_ptr)
	{

	}


	CCamera::CCamera(): m_Fov(120.0f), m_AspectRatio(16.0f/9.0f), m_Near(0.0001f), m_Far(1000.0f)
	{

	}

	mat4 CCamera::projection()
	{
		return glm::perspective(glm::radians(m_Fov.get()), m_AspectRatio.get(), m_Near.get(), m_Far.get());
	}
	void CCamera::set_fov(float new_fov)
	{
		m_Fov = new_fov;
	}
	void CCamera::set_near(float new_near)
	{
		m_Near = new_near;
	}
	void CCamera::set_far(float new_far)
	{
		m_Far = new_far;
	}
	void CCamera::set_aspect(float new_aspect)
	{
		m_AspectRatio = new_aspect;
	}

}