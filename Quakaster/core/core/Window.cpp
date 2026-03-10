#include "Window.h"
#include <GLFW/glfw3.h>
#include "../platform/glfw_EventTranslator.h"
#include "spdlog/spdlog.h"
#include <stdexcept>
namespace qk {

	void Window::set_key_callback(GLFWkeyfun callback) {
		glfwSetKeyCallback(m_Window, callback);
	}

	void Window::set_event_queue(EventQueue* queue) {
		m_Queue = queue;
	}


	EventQueue* Window::queue() {
		return m_Queue;
	}

	void Window::make_context_current() {
		if (!m_Window) {
			throw std::runtime_error("Window not initialized!");
		}
		glfwMakeContextCurrent(m_Window);  // <-- this is the key
	}

	Window::Position Window::get_position() {
		Position result;
		glfwGetWindowPos(m_Window, &(result.x), &(result.y));
		return result;
	}

	void Window::set_position(Window::Position new_position) {
		
		glfwSetWindowPos(m_Window, new_position.x, new_position.y);
	}

	std::string Window::get_title() {
		return std::string(glfwGetWindowTitle(m_Window));
	}

	void Window::pollEvents() {
		glfwPollEvents();
	}

	int Window::should_close() {
		return glfwWindowShouldClose(m_Window);
	}

	void Window::swap_buffers() {
		glfwSwapBuffers(m_Window);
	}
	void Window::resize(Window::Size new_size) {
		glfwSetWindowSize(m_Window, new_size.w, new_size.h);
	}
	void* Window::handle() {
		return m_Window;
	}



	void Window::init(Window::Size initial_size, const std::string& title, Monitor monitor, Window* shared) {
		spdlog::info("Window initialized at {:#x}", (uintptr_t)this);

		m_Window = glfwCreateWindow(initial_size.w, initial_size.h, title.c_str(),
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

	void Window::destroy() {
		spdlog::info("Window destroyed at {:#x}", (uintptr_t)this);
		if (m_Window) {
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
		}
	}


	Window::~Window() {
		destroy();
	}

}