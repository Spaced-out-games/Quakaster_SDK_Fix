#pragma once
#include "Stopwatch.h"
#include "../core.h"
#include <stdint.h>

namespace qk {
	struct IService: Stopwatch {


		virtual ~IService() = default;
		virtual void init() = 0;
		virtual void shutdown() = 0;


	};
}