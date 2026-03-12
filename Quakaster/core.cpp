#include "core.h"
#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"

namespace qk {

	static void glfw_error_callback(int error, const char* description) {
		__debugbreak();
		spdlog::error("GLFW Error {}: {}", error, description);
	}

    bool init(int major, int minor) {

        glfwSetErrorCallback(glfw_error_callback);

        if (!glfwInit())
            return false;

        spdlog::info("Initialized glfw");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);


        return true;
    }
	void close() {
		spdlog::info("Terminated glfw");
		glfwTerminate();
	}
}