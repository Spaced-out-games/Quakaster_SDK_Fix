#include "core.h"
#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"

namespace qk {

	static void glfw_error_callback(int error, const char* description) {
		__debugbreak();
		spdlog::error("GLFW Error {}: {}", error, description);
	}

	bool init(int major, int minor) {

		spdlog::info("Initialized glfw");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor); // or 4.5
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwSetErrorCallback(glfw_error_callback);
		return glfwInit() == GLFW_TRUE;
	}
	void close() {
		spdlog::info("Terminated glfw");
		glfwTerminate();
	}
}