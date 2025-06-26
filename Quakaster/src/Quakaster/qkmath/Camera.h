#pragma once
#include "qkmath.h"
#include "../Core.h"






namespace qk
{
	class QK_API Camera
	{
		

		float m_Fov; // might be controlled by r_fov
		float m_Near; // might be controlled by r_near
		float m_Far; // might be controlled by r_far
		float m_AspectRatio; // might be controlled by r_aspect

		public:
		
		// Creates a camera with its state stored internally.
		Camera(float FOV, float Aspect, float Near, float Far);



		// Default camera binds to convars
		Camera();

		// Gets the projection matrix
		mat4 projection();

		// some getters and setters to come...
		void set_fov(float new_fov);
		void set_near(float new_near);
		void set_far(float new_far);
		void set_aspect(float new_aspect);
	};
}