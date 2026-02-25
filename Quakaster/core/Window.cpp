#include "Window.h"
#include <GLFW/glfw3.h>
#include "glfw_EventTranslator.h"

namespace qk {

	void Window::set_key_callback(GLFWkeyfun callback) {
		glfwSetKeyCallback(m_Window, callback);
	}

	void Window::set_event_queue(std::shared_ptr<EventQueue> queue) {
		m_Queue = queue;
	}


	EventQueue* Window::queue() {
		return m_Queue.get();
	}


	glm::ivec2 Window::get_position() {
		glm::ivec2 result;
		glfwGetWindowPos(m_Window, &(result.x), &(result.y));
		return result;
	}

	void Window::set_position(glm::ivec2 new_position) {
		
		glfwSetWindowPos(m_Window, new_position.x, new_position.y);
	}

	std::string Window::get_title() {
		return std::string(glfwGetWindowTitle(m_Window));
	}

	void Window::pollEvents() {
		glfwPollEvents();
	}



	void Window::init(int width, int height, const std::string& title, Monitor monitor, Window* shared) {
		m_Window = glfwCreateWindow(width, height, title.c_str(),
			(GLFWmonitor*)monitor,
			shared ? shared->m_Window : nullptr);

		if (!m_Window) {
			// handle error
			return;
		}

		// Now m_Window is valid — safe to set user pointer and callbacks
		glfwSetWindowUserPointer(m_Window, this);
		set_key_callback(qk::EventCallbacks::on_key);
	}

	Window::Window() {

	}

	Window::~Window() {
		glfwDestroyWindow(m_Window);
	}

}