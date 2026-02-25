#pragma once
#include "core/Application.h"
#include <memory>

namespace qk {
	extern std::unique_ptr<qk::Application> create_application(int argc, char** argv);
}


int main(int argc, char** argv) {
	std::unique_ptr<qk::Application> app = qk::create_application(argc, argv);
	app->run();
}