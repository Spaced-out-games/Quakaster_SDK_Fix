#pragma once
#include "qk/Application.h"

extern qk::Application* create_application(int argc, char** argv);

// Calls the client-defined create_application() function, runs that application, then deletes it. Super simple
int main(int argc, char** argv) {
	qk::Application* app = create_application(argc, argv);
	app->init();
	int result = app->run();
	app->destroy();
	delete app;
	return result;
}