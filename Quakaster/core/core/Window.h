#pragma once
#include "../../core.h"
#define GLFW_INCLUDE_NONE
#include <string>
#include <memory>
#include "../io/EventQueue.h"


struct GLFWwindow;
struct GLFWmonitor;
typedef void (*GLFWkeyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);

namespace qk {

	using Monitor = GLFWmonitor*;


	

	class QK_API Window {
		GLFWwindow* m_Window = nullptr;
		EventQueue* m_Queue = nullptr;

		
		public:

			struct Position {
				int x = 0;
				int y = 0;
			};
			struct Size {
				int w = 0;
				int h = 0;
			};

			void make_context_current();
			void set_key_callback(GLFWkeyfun callback);
			void set_event_queue(EventQueue* queue);
			EventQueue* queue();
			Window::Position get_position();
			void set_position(Window::Position new_position);

			std::string get_title();

			int should_close();
			void init(Window::Size initial_size, const std::string& title, Monitor monitor = nullptr, Window* shared = nullptr);
			void swap_buffers();
			void resize(Window::Size new_size);
			void* handle();
			void destroy();
			Window();
			~Window();

			
			void pollEvents();

	};
}