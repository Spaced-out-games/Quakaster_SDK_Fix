#pragma once

#if defined(QK_GRAPHICS_BACKEND)
	#if(QK_GRAPHICS_BACKEND == 1)
		#include "GL/VAO.h"
		//#include "GL/VBO.h"
		#include "GL/EBO.h"
		#include "GL/ShaderInstance.h"
		#include "GL/ShaderSources.h"
		#include "GL/GraphicsPipeline.h"
		#include "GL/graphics_init.h"
		#include <Quakaster/qkg/GL/MeshConfiguration.h>w
		#include "Quakaster/qkg/GL/Mesh.h"
		//#include "GL/Window.h"
	#else // other backends

	#endif
#else // no backend

#endif




