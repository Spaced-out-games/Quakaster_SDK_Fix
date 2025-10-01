#pragma once
#include <string_view>
#include <string>
#include "../qk/QKTL.h"
#include <entt/core/hashed_string.hpp>

namespace qk::kernel
{
	enum class ERestrictionFlags: uint32_t
	{
		RESTRICT_NONE = 0,
		// must have sv_cheats enabled
		RESTRICT_CHEAT = BIT(0)
	};

	inline ERestrictionFlags operator&(ERestrictionFlags lhs, ERestrictionFlags rhs)
	{
		return (ERestrictionFlags)((uint32_t)lhs & (uint32_t)rhs);
	}

	struct Kernel;

	using Command_pfn = func_ptr_t<void, Kernel&, std::string&>;

	struct Command
	{
		entt::hashed_string m_Name;
		ERestrictionFlags m_Flags;
		Command_pfn m_Func;

		Command(entt::hashed_string name, ERestrictionFlags flags, Command_pfn function);
		Command() = default;
		void call(Kernel& kernel, std::string args, ERestrictionFlags permissions = ERestrictionFlags::RESTRICT_NONE);
		

		inline std::string_view name();

		inline entt::id_type hash();

	};
}