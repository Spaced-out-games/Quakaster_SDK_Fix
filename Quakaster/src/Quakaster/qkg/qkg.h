#pragma once

#if defined(QK_GRAPHICS_BACKEND)
	#if(QK_GRAPHICS_BACKEND == 1)
		#include "GL/VAO.h"
		#include "GL/VBO.h"
		#include "GL/EBO.h"
		#include "GL/ShaderInstance.h"
		#include "GL/Shader.h"
		#include "GL/GraphicsPipeline.h"
		//#include "GL/Window.h"
		#include "GL/graphics_init.h"
	#else // other backends

	#endif
#else // no backend

#endif




