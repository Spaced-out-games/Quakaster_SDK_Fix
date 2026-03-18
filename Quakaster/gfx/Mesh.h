/// **************************************** QUAKASTER ENGINE **************************************** 
/// gfx/Mesh.h
/// Purpose:
/// **************************************************************************************************
/// 
/// 
#pragma once
#include "../core.h"
#include "CMeshInstance.h"

namespace qk::gfx {

	struct QK_API Mesh {
		unsigned int m_vbo = 0;



		unsigned int add_instance();

	};

}