#include "KTerminalModule.h"

namespace qk::kernel
{

	int clear_cmd(Kernel& kernel, std::span<const Token> args)
	{
		kernel.print("\033[2J\033[1;1H");
		return 0;
	}


	int echo_cmd(Kernel& kernel, std::span<const Token> args)
	{
		for (auto& token : args)
		{
			kernel.m_stdout = token;
		}

		return 0;
	}

	bool KTerminalModule::mount(Kernel& kernel)
	{
		kernel.register_fn("clear", &clear_cmd);
		kernel.register_fn("echo", &echo_cmd);
		return true;
	}
	bool KTerminalModule::unmount(Kernel& kernel)
	{
		return true;
	}
}