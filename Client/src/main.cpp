#include <iostream>
#include "entrypoint.h"
#include "core/Window.h"
#include "core/EventQueue.h"
#include <thread>
#include <stdint.h>
#include "core/DefaultEvents.h"
#include "core/LayerStack.h"
#include "core/ServiceManager.h"


#include "DummyService.h"
#include "TestLayer.h"
#include "GreetLayer.h"

struct MyApp : qk::Application {
	qk::Window window;
	std::shared_ptr<qk::EventQueue> queue;
	qk::LayerStack stack;
	size_t max = 0;
	qk::ServiceManager mgr;
	entt::registry registry;

	void init(int argc, char** argv) override {
		qk::init();
		queue = std::make_unique<qk::EventQueue>();
		window.init(480, 480, "Demo");
		window.set_event_queue(queue);
		stack.attach_queue(queue);
		stack.insert_layer(std::make_unique<TestLayer>());
		stack.insert_layer(std::make_unique<GreetLayer>());
		mgr.registry = &registry;
		mgr.add_service<DummyService>("DummyService");

		DummyService* dummy = dynamic_cast<DummyService*>(mgr.get_service("DummyService"));

		if (dummy) std::cout << dummy->name;


		mgr.remove_service("DummyService");

	}

	void run() override {

		max = std::max(max, window.queue()->size());

		std::cout << max << '\n';
		window.queue()->clear();
		std::this_thread::sleep_for(std::chrono::milliseconds(17));
		window.pollEvents();
		stack.propagate_events();


	}



};

std::unique_ptr<qk::Application> qk::create_application(int argc, char** argv) {
	return std::make_unique<MyApp>();
}

