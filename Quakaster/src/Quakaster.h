#pragma once
// Quakaster.h
// PURPOSE: Using macros defined in modules.h, includes modules into the built DLL
// APPLICATION INCLUSION ONLY!!!




#define QK_GRAPHICS_BACKEND_GL
#define INCLUDE_QKENT

// Includes all the core functionalities
// This NEEDS to be loaded first so that proceeding includes have access to it.
#include "Quakaster/Core.h"
#include "Quakaster/qklog/logging.h"
#include "Quakaster/EntryPoint.h"

#include "Quakaster/qkmath/qkmath.h"

// load the appropriate backend

#ifdef QK_GRAPHICS_BACKEND_GL
#include "Quakaster/qkg/GL/import.h"
#endif

#include "Quakaster/qkui/import.h"

#ifdef INCLUDE_QKENT
	//#include "Quakaster/qkent/"
#endif
