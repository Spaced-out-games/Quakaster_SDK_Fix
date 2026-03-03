#pragma once
#include "Shader.h"
#include "../core.h"

namespace gfx {
	struct QK_API ShaderProgram {
		unsigned int m_Handle = 0;

		bool init(const Shader& frag, const Shader& vert);

		void bind();

		static void unbind();

	};
}