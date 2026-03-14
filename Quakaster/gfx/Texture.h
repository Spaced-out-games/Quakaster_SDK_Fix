#pragma once
#include "../core.h"
#include "types.h"
#include "../core/res/Image.h"
namespace gfx {

	static unsigned int filter_mode = 0x2600; // GL_NEAREST

	class QK_API Texture {
		Handle m_Handle = 0;
		unsigned int m_Type = 0;
		public:
			Texture() = default;
			void init(qk::Image& img, unsigned int type);
			void bind();
			Handle handle() const;
	};
}