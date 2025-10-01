#include "kernel_instruction.h"

namespace qk::kernel
{
	Instruction::Instruction(const char* name, std::string args):
		m_Arguments(args)
	{
		m_ID = entt::hashed_string{ name }.value();
	}
}