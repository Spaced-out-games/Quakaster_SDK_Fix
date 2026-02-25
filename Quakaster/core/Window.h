#pragma once
#include "../core.h"
#define GLFW_INCLUDE_NONE
#include <string>


struct GLFWwindow;
struct GLFWmonitor;

namespace qk {

	using Monitor = GLFWmonitor*;


	class QK_API Window {
		GLFWwindow* m_Window = nullptr;
		public:
			void init(int initial_width, int initial_height, const std::string& title, Monitor monitor = nullptr, Window* shared = nullptr);
			Window();
			~Window();
	};
}