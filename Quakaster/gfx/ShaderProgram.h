#pragma once
#include "Shader.h"
#include "../core.h"
#include "types.h"

namespace gfx {
	class QK_API ShaderProgram {
		Handle m_Handle = NULL_HANDLE;

		public:

			bool init(const Handle frag, const Handle vert);

			void bind();

			static void unbind();

	};
}