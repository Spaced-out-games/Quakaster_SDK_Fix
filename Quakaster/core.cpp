#include "core.h"
#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"

namespace qk {

	static void glfw_error_callback(int error, const char* description) {
		__debugbreak();
		spdlog::error("GLFW Error {}: {}", error, description);
	}

	bool init() {

		spdlog::info("Initialized glfw");
		glfwSetErrorCallback(glfw_error_callback);
		return glfwInit() == GLFW_TRUE;
	}
	void close() {
		spdlog::info("Terminated glfw");
		glfwTerminate();
	}
}