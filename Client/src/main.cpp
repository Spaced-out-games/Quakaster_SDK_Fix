#include <iostream>
#include "entrypoint.h"
#include "core/Window.h"
#include "core/EventQueue.h"
#include <thread>
#include <stdint.h>
struct MyApp : qk::Application {
	qk::Window window;
	std::shared_ptr<qk::EventQueue> queue;
	size_t max = 0;

	void init(int argc, char** argv) override {
		qk::init();
		queue = std::make_unique<qk::EventQueue>();
		window.init(480, 480, "Demo");
		window.set_event_queue(queue);
	}

	void run() override {

		max = std::max(max, window.queue()->size());

		std::cout << max << '\n';
		window.queue()->clear();
		std::this_thread::sleep_for(std::chrono::milliseconds(17));
		window.pollEvents();

	}



};

std::unique_ptr<qk::Application> qk::create_application(int argc, char** argv) {
	return std::make_unique<MyApp>();
}

