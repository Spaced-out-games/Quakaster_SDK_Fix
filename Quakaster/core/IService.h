#pragma once
#include "../core.h"
#include <stdint.h>
#include "../core.h"
namespace qk {
	struct QK_API IService {

		protected:
			size_t m_Uptime_ns = 0;


		public:
			size_t* uptime_ptr();
			size_t uptime_ns();

			virtual ~IService() = default;
			virtual void init();
			virtual void shutdown();


	};
}