#include "Window.h"
#include <GLFW/glfw3.h>

namespace qk {
	void Window::init(int initial_width, int initial_height, const std::string& title, Monitor monitor, Window* shared) {


		glfwCreateWindow(initial_width, initial_height, title.c_str(), (GLFWmonitor*)monitor, shared ? shared->m_Window: nullptr);
	}

	Window::Window() {

	}

	Window::~Window() {
		glfwDestroyWindow(m_Window);
	}

}