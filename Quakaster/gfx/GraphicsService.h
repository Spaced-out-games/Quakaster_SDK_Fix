#pragma once
#include "GraphicsPrimitiveService.h"
#include "../core.h"
namespace gfx {

	struct Mesh {
		unsigned int vao = 0;
		std::vector<unsigned int> vbos;
	};

	// TODO: Move the internals of GraphicsPrimitiveService into Mesh
	struct QK_API GraphicsService: public GraphicsPrimitiveService {
		
		

	};

}