#include <iostream>
#include "../entrypoint.h"
struct MyApp : qk::Application {
	void run() override {
		std::cout << "hello world";
	}
};

std::unique_ptr<qk::Application> qk::create_application(int argc, char** argv) {
	return std::make_unique<MyApp>();
}

