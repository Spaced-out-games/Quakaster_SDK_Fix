#pragma once
// Quakaster.h
// PURPOSE: Using macros defined in modules.h, includes modules into the built DLL
// APPLICATION INCLUSION ONLY!!!





#define INCLUDE_QKENT

// Includes all the core functionalities
// This NEEDS to be loaded first so that proceeding includes have access to it.
#include "Quakaster/Core.h"
#include "Quakaster/EntryPoint.h"

// load the appropriate backend

namespace qkg
{
    enum class Backend {
        NONE,
        GL,
        VK,
        DX,
        // Add more as needed
    };
}





//#include "Quakaster/qkui/import.h"


