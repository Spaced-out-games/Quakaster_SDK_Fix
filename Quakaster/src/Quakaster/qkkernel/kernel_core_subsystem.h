#pragma once
#include "../Core.h"
#include "kernel_subsystem.h"
#include "kernel_core.h"


namespace qk::kernel::core
{
	struct QK_API CoreSubsystem : qk::kernel::Subsystem
	{
		CoreSubsystem(int pid);
		// Since this subsystem is the core of the kernel, it only needs to register
		// a few commands and that's basically it.
		bool mount(Kernel& kernel) override;
		std::string current_task()  const;
		void shutdown() override;
	};
}