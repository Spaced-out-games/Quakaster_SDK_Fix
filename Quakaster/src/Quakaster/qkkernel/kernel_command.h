#pragma once
#include <string_view>
#include <string>
#include "../qk/QKTL.h"

namespace qk::kernel
{
	enum class ERestrictionFlags
	{
		RESTRICT_NONE = 0,
		// must have sv_cheats enabled
		RESTRICT_CHEAT = BIT(0)
	};

	struct Kernel;

	using Command_pfn = func_ptr_t<void, Kernel&, const std::vector<std::string>&>;

	struct Command
	{
		entt::hashed_string m_Name;
		ERestrictionFlags m_Flags;
		Command_pfn m_Func;

		Command(entt::hashed_string name, ERestrictionFlags flags, Command_pfn function);

		void operator()(Kernel& kernel, const std::vector<std::string>& args, ERestrictionFlags permissions)
		{
			if (m_Func)
			{
				if ((permissions & m_Flags) == m_Flags)
				{
					m_Func(kernel, args);
				}
				else
				{
					kernel.fd_err += "Permission denied.\n"
				}

			}
			else
			{
				kernel.fd_err += "Invalid command\n"
			}

		}

		inline std::string_view name();

		inline entt::id_type hash();

	};
}