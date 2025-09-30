#include "kernel.h"


namespace qk::kernel
{
	void Kernel::clear()
	{
		fd_select.clear();
		fd_out = "";
		fd_err = "";
	}

	void Kernel::flush()
	{
		std::cout << fd_out;
		std::cerr << fd_err;
		clear();
	}

	void Kernel::register_command(entt::hashed_string name, ERestrictionFlags flags, Command_pfn func)
	{
		command_table[name.value()] = Command(name, flags, func);
	}

	void Kernel::execute_program(Program* program, ERestrictionFlags permissions)
	{
		if (!program) return;

		for (const auto& instr : *program)
		{
			auto it = command_table.find(instr.m_ID);
			if (it != command_table.end())
			{
				Command& cmd = it->second;
				cmd(*this, instr.m_Arguments, permissions);
			}
			else
			{
				fd_err += "Unknown command\n";
			}
		}
	}
}