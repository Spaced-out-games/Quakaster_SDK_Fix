#pragma once
#include <entt/core/hashed_string.hpp>
#include <stdint.h>
#include <vector>
#include <string>

namespace qk::kernel
{
	using instruction_id_t = entt::id_type;
	struct Instruction
	{
			instruction_id_t m_ID;
			std::vector<std::string> m_Arguments;
	};
}