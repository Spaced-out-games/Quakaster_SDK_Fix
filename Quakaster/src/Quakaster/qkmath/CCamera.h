#pragma once
#include "../qk/QKTL.h"
#include "qkmath.h"
#include "../Core.h"



//class FloatPtrUnion;


namespace qk
{
	class QK_API CCamera
	{
		FloatPtrUnion m_Fov;
		FloatPtrUnion m_Near;
		FloatPtrUnion m_Far;
		FloatPtrUnion m_AspectRatio;

		public:
		
		// Creates a camera with its state stored internally.
		CCamera(float FOV, float Aspect, float Near, float Far);

		// Creates a camera with its state bound
		CCamera(float* FOV_ptr, float* Aspect_ptr, float* Near_ptr, float* Far_ptr);





		// Default camera binds to convars
		CCamera();

		// Gets the projection matrix
		mat4 projection();

		// some getters and setters to come...
		void set_fov(float new_fov);
		void set_near(float new_near);
		void set_far(float new_far);
		void set_aspect(float new_aspect);
	};
}