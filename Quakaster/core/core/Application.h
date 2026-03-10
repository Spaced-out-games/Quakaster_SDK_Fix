#pragma once
#include "../../core.h"

namespace qk {
	class QK_API Application {
		int m_Status = 0;

		public:
		Application();
		virtual ~Application();
		virtual void init(int argc, char** argv);
		virtual void run() = 0;
		virtual void close();
		int status();
		void set_status(int new_status);
	};
}

