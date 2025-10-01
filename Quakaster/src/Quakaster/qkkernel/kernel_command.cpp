#include "kernel_command.h"
#include "kernel.h"

namespace qk::kernel
{

	Command::Command(entt::hashed_string name, ERestrictionFlags flags, Command_pfn func) :
		m_Name(name),
		m_Flags(flags),
		m_Func(func)
	{

	}

	std::string_view Command::name()
	{
		return std::string_view(m_Name.data(), m_Name.data() + m_Name.size());
	}
	entt::id_type Command::hash()
	{
		return m_Name.value();
	}

	void Command::call(Kernel& kernel, std::string args, ERestrictionFlags permissions)
	{
		if (m_Func)
		{
			if ((permissions & m_Flags) == m_Flags)
			{
				m_Func(kernel, args);
			}
			else
			{
				kernel.m_FD_err += "'";
				kernel.m_FD_err += m_Name.data();
				kernel.m_FD_err += "' failed: Permission denied.\n";
			}

		}
		else
		{
			kernel.m_FD_err += "Invalid command\n";
		}

	}
}