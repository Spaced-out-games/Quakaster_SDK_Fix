#pragma once
#include "../core.h"
#include "CMeshInstance.h"

namespace gfx {

	struct QK_API Mesh {
		unsigned int m_vbo = 0;



		unsigned int add_instance();

	};

}