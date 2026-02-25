#include "Application.h"



namespace qk {
	Application::Application() {

	}

	Application::~Application() {

	}
	int Application::status() {
		return m_Status;
	}

	void Application::init(int argc, char** argv) {}

	void Application::close() {}
}