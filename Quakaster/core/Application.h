#pragma once
#include "../core.h"

namespace qk {
	struct QK_API Application {
		Application();
		virtual ~Application();
		

		virtual void run() = 0;
	};
}

