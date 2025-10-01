#pragma once
#include <entt/entity/entity.hpp>
#include "../Core.h"
#include <unordered_map>
#include "kernel_program.h"
#include "kernel_command.h"
using namespace entt::literals;


namespace qk::kernel
{
	struct Command;
	struct Instruction;

	struct QK_API Kernel
	{
		std::unordered_map<instruction_id_t, Command>	m_Operator_table;
		std::unordered_map<instruction_id_t, Command>	m_Command_table;
		std::vector<entt::entity>						m_FD_select;
		entt::registry*									m_Registry;
		Program*										m_Program;
		std::string										m_FD_out;
		std::string										m_FD_err;
		bool											m_KeepFD;
		uint64_t										m_ip;
		Kernel();
		inline void clear();

		inline void flush();

		inline void register_command(entt::hashed_string name, ERestrictionFlags flags, Command_pfn func);

		inline void execute_program(Program* program, ERestrictionFlags permissions);

		inline void print_everything();

		inline void assign_registry(entt::registry* registry);
		

	};
}