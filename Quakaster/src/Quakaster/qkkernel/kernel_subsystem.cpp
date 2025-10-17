#include "kernel_subsystem.h"


namespace qk::kernel
{
	Subsystem::Subsystem(int pid):
		pid(pid),
		start_time(std::chrono::steady_clock::now())
	{
	}
	Subsystem::~Subsystem()
	{

	}

	void Subsystem::shutdown()
	{

	}

	std::chrono::steady_clock::duration Subsystem::uptime() const
	{
		return std::chrono::steady_clock::now() - start_time;
	}

	std::string Subsystem::current_task() const
	{
		return "RUNNING...";
	}

}