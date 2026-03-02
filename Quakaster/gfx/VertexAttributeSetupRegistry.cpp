#include "VertexAttributeSetupRegistry.h"
#include "GL/glew.h"

namespace gfx {

	void add_vertex_attribute_pointer_impl(unsigned int& location, int num_components, unsigned int component_type, bool normalized, int stride, uintptr_t offset_bytes) {
		// don't forget this is called ahead of time, with VBO!!!
		//  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, num_components, component_type, normalized, stride, reinterpret_cast<const void*>(offset_bytes));
	}

	std::unordered_map<std::type_index, VertexAttributeSetupRegistry::setup_lambda_t>& VertexAttributeSetupRegistry::registry() {
		return m_SetupRegistry;
	}

}