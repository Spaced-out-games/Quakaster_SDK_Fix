#pragma once
#include "../../Core.h"
#include "GL/glew.h"

alignas(32) class QK_API CMeshInstance
{
	public:

	// Which mesh configuration we are using
	GLuint m_VAO = 0;

	// which mesh we are using
	GLuint m_VBO = 0;

	// Which mesh instance we are working with
	uint32_t m_InstanceIndex = 0;


	// Sets an instance_t, this is NOT a complete concept, here for future reference

	//template <class instance_t>
	//void upload_data(const instance_t& new_value, qkg::MeshRegistry& registry);
};