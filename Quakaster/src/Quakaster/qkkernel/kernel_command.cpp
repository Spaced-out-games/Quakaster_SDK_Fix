#include "kernel_command.h"

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
}