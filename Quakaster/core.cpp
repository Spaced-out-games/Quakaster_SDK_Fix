#include "core.h"
#include <GLFW/glfw3.h>

namespace qk {
	bool init() {
		return glfwInit() == GLFW_TRUE;
	}
}