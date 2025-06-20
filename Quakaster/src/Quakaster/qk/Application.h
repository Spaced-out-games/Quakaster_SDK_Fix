// Application.h
// PURPOSE: Defines a Application interface. No implementation beyond setting up GLFW. 

#pragma once
#include "../Core.h"
#include "../qklog/logging.h"

namespace qk {

	struct QK_API Application {
		virtual ~Application();
		// Initializes the application
		virtual void init() = 0;

		// Runs the application game loop
		virtual int run() = 0;
		// Cleans up resources
		virtual void destroy() = 0;

		Application(int argc, char** argv);

	};

}

// Client-defined function
qk::Application* create_application(int argc, char** argv);
