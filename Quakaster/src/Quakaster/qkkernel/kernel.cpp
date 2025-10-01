#include "kernel.h"
#include <fstream>

namespace qk::kernel
{

	Kernel::Kernel()
	{

		register_command("echo"_hs, ERestrictionFlags::RESTRICT_NONE, [](Kernel& kernel, std::string& args)
			{
				kernel.m_FD_out += args;
				kernel.m_KeepFD = 0;
			}
		);
		register_command("cat"_hs, ERestrictionFlags::RESTRICT_NONE, [](Kernel& kernel, std::string& args) {

			std::string path = kernel.m_FD_out;
			std::ifstream file(path);

			if (file)
			{
				kernel.m_FD_out = std::string(
					std::istreambuf_iterator<char>(file),
					std::istreambuf_iterator<char>()
				);
				return;
			}
			else {
				kernel.m_FD_err += "could not find file: \"";
				kernel.m_FD_err += path;
				kernel.m_FD_err += "\"\n";
			}
			});








		m_Operator_table["|"_hs.value()] = Command(
			"|"_hs,
			ERestrictionFlags::RESTRICT_NONE,
			[](Kernel& kernel, std::string& args)
			{
				kernel.m_KeepFD = 1;
			}
		);

		m_Operator_table[";"_hs.value()] = Command(
			";"_hs,
			ERestrictionFlags::RESTRICT_NONE,
			[](Kernel& kernel, std::string& args)
			{
				kernel.m_KeepFD = 0;
				kernel.print_everything();
			}
		);
	}


	void Kernel::clear()
	{
		m_FD_select.clear();
		m_FD_out = "";
		m_FD_err = "";
	}

	void Kernel::flush()
	{
		std::cout << m_FD_out;
		std::cerr << m_FD_err;
		clear();
	}

	void Kernel::register_command(entt::hashed_string name, ERestrictionFlags flags, Command_pfn func)
	{
		m_Command_table[name.value()] = Command(name, flags, func);
	}

	inline void Kernel::assign_registry(entt::registry* registry)
	{
		m_Registry = registry;
	}

	void Kernel::print_everything()
	{
		std::cerr << m_FD_err << '\n';
		std::cout << m_FD_out << '\n';
		size_t i = 0;
		std::cout << "Entities: {";
		for (; i < m_FD_select.size(); i++)
		{
			std::cout << (uint32_t)m_FD_select[i] << ", ";
		}
		std::cout << "}\n";
		clear();
	}

	void Kernel::execute_program(Program* program, ERestrictionFlags permissions)
	{
		if (!program) return;
		int debug_ctr = 0;
		
		for (int index = 0; index < program->size(); index++)
		{
			const auto& instr = program->at(index);

			auto command_it = m_Command_table.find(instr.m_ID);
			auto operator_it = m_Operator_table.find(instr.m_ID);


			
			if (command_it != m_Command_table.end())
			{

				
				Command& cmd = command_it->second;

				// clears the pipeline
				if (!m_KeepFD)
					clear();
				cmd.call(*this, instr.m_Arguments, permissions);

			}
			else if (operator_it != m_Operator_table.end())
			{
				operator_it->second.call(*this, instr.m_Arguments, permissions);
			}
			else
			{
				m_FD_err += "Unknown command\n";
			}

			if (index == program->size() - 1)
			{
				print_everything();
			}

		}

	}

}