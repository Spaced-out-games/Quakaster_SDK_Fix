#include "KTerminalModule.h"
#include "KernelIdentifierTable.h"

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
	int printenv_cmd(Kernel& kernel, std::span<const Token> args)
	{
		StringToken result;
		for (auto& hash_name : id::lut())
		{
			result += '$';
			result += hash_name.second;
			result += ": ";
			result += kernel.m_Env[hash_name.first].print_str();
			result += '\n';
		}
		kernel.m_stdout = result;
		return 0;
	}

	bool KTerminalModule::mount(Kernel& kernel)
	{
		kernel.register_fn("clear", &clear_cmd, "Terminal");
		kernel.register_fn("echo", &echo_cmd, "Terminal");
		kernel.register_fn("printenv", &printenv_cmd, "Terminal");

		return true;
	}
	bool KTerminalModule::unmount(Kernel& kernel)
	{
		return true;
	}
	KTerminalModule::KTerminalModule(std::string name, SSID id): KModuleBase(std::move(name), id) {}
}