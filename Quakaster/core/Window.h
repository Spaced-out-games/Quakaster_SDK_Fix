#pragma once
#include "../core.h"
#define GLFW_INCLUDE_NONE
#include <string>
#include <memory>
#include <glm/vec2.hpp>
#include "EventQueue.h"


struct GLFWwindow;
struct GLFWmonitor;
typedef void (*GLFWkeyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);

namespace qk {

	using Monitor = GLFWmonitor*;


	class QK_API Window {
		GLFWwindow* m_Window = nullptr;
		std::shared_ptr<EventQueue> m_Queue = nullptr;

		
		public:
			void set_key_callback(GLFWkeyfun callback);
			void set_event_queue(std::shared_ptr<EventQueue> queue);
			EventQueue* queue();
			glm::ivec2 get_position();
			void set_position(glm::ivec2 new_position);

			std::string get_title();

			void init(int initial_width, int initial_height, const std::string& title, Monitor monitor = nullptr, Window* shared = nullptr);
			Window();
			~Window();

			
			void pollEvents();

	};
}