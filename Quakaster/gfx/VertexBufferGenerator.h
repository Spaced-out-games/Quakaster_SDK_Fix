#pragma once
#include "GL/glew.h"
#include <typeindex>
#include "../core/IService.h"


namespace gfx {

	using VertexBufferGenerator_pfn = unsigned int(*)(const void* data, size_t size, unsigned int usage);

	struct VertexBufferGenerator {
		VertexBufferGenerator_pfn	impl = nullptr;
		std::type_index				type = (typeid(void));

		unsigned int operator()(const void* data, size_t size, unsigned int usage) {
			if (!impl) return 0;
			return impl(data, size, usage);
		}

		VertexBufferGenerator() = default;

	};

}