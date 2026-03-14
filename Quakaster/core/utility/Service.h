#pragma once
#include <stdint.h>
#include "../../core.h"
namespace qk {
	struct QK_API IService {

		protected:
			uint64_t m_Uptime_ns = 0;


		public:
			uint64_t* uptime_ptr();
			uint64_t uptime_ns();

			virtual ~IService() = default;
			virtual void init();
			virtual void shutdown();
			void clear_timer();

	};
}