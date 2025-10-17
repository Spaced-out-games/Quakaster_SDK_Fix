#include "kernel_core_subsystem.h"

namespace qk::kernel::core
{
	CoreSubsystem::CoreSubsystem(int pid): Subsystem(pid) {}

	bool CoreSubsystem::mount(Kernel& kernel)
	{
		kernel.register_fn("echo", &qk::kernel::core::echo);
		kernel.register_fn("cd", &qk::kernel::core::cd);
		kernel.register_fn("pwd", &qk::kernel::core::pwd);
		kernel.register_fn("clear", &qk::kernel::core::clear);
		kernel.register_fn("wc", &qk::kernel::core::wc);
		kernel.register_fn("exit", &qk::kernel::core::exit);
		kernel.register_fn("wf", &qk::kernel::core::wf);
		kernel.register_fn("cat", &qk::kernel::core::cat);
		kernel.register_fn("set", &qk::kernel::core::set);
		kernel.register_fn("run", &qk::kernel::core::run);
		kernel.register_fn("ps", &qk::kernel::core::ps);

		return 1;
	}
	std::string CoreSubsystem::current_task() const
	{
		return "testing...";
	}
	void CoreSubsystem::shutdown()
	{

	}
}