#include <iostream>
#include "entrypoint.h"
#include "core/Window.h"
struct MyApp : qk::Application {
	qk::Window window;

	void init(int argc, char** argv) override {
		qk::init();
		window.init(480, 480, "Demo");
	}

	void run() override {

	}



};

std::unique_ptr<qk::Application> qk::create_application(int argc, char** argv) {
	return std::make_unique<MyApp>();
}

