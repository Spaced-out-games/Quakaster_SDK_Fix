#pragma once
#include "core/IService.h"

struct DummyService : qk::IService {
	std::string name = "dummy buddy";
	void init() override {}
	void shutdown() override {}
};