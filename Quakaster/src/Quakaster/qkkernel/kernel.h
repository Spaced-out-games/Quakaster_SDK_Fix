#pragma once
#include <entt/entity/entity.hpp>
#include "../Core.h"
#include <unordered_map>
#include "kernel_program.h"
#include "kernel_command.h"


namespace qk::kernel
{
	struct QK_API Kernel
	{
		std::unordered_map<instruction_id_t, Command_pfn> command_table;
		std::vector<entt::entity> fd_select;
		std::string fd_out;
		std::string fd_err;
		uint64_t ip = 0;
		Program* program = nullptr;

		inline void clear();

		inline void flush();

		inline void register_command(entt::hashed_string name, ERestrictionFlags m_Flags, Command_pfn m_Func);

		inline void execute_program(Program* program, ERestrictionFlags permissions);

	};
}