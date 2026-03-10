#include "glfw_EventTranslator.h"
#include "../io/DefaultEvents.h"
#include "../io/Event.h"
#include "../core/Window.h"


namespace qk::EventCallbacks {
	void on_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window* target = (Window*)glfwGetWindowUserPointer(window);


		if (!target->queue()) return;

		KeyEvent& kv = (KeyEvent&)target->queue()->emplace_back();

		kv.m_Category = EEventCategory::cat_keyboard;
		switch (action) {
			case GLFW_PRESS:  kv.m_Type = EEventType::KeyPress_evt; break;
			case GLFW_REPEAT: kv.m_Type = EEventType::KeyHold_evt;  break;
			case GLFW_RELEASE:kv.m_Type = EEventType::KeyRelease_evt; break;
		}



		kv.key() = key;
		kv.scancode() = scancode;
		kv.mods() = mods;

	}
}