#pragma once
#include "../Core.h"
#include <entt/core/hashed_string.hpp>
#include <stdint.h>
#include <vector>
#include <string>

namespace qk::kernel
{
	using instruction_id_t = entt::id_type;
	struct QK_API Instruction
	{
			instruction_id_t m_ID;
			std::string m_Arguments;
			Instruction(const char* name, std::string args);
	};
}