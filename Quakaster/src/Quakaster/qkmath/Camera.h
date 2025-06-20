#pragma once
#include "qkmath.h"
#include "../Core.h"

#ifdef INCLUDE_QKENT
	#include <entt/entt.hpp>
#endif


namespace qk
{
	class QK_API Camera
	{
		

		tagged_float m_Fov; // might be controlled by r_fov
		tagged_float m_Near; // might be controlled by r_near
		tagged_float m_Far; // might be controlled by r_far
		tagged_float m_AspectRatio; // might be controlled by r_aspect

		public:
		
		// Creates a camera with its state stored internally.
		Camera(float FOV, float Aspect, float Near, float Far);

		// Creastes a camera with its state stored externally. Great for linking against convars
		Camera(float* FOV_ptr, float* Aspect_ptr, float* Near_ptr, float* Far_ptr);
		
		// Gets the projection matrix
		mat4 projection();

		// some getters and setters to come...

	};
}