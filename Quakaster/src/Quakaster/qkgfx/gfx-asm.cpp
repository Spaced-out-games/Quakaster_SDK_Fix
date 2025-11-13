#include "gfx-asm.h"






namespace qk::gfx
{
	//std::string to_string(Command cmd)
	//{
	//	return std::format("{} {};", cmd.m_Opcode, cmd.m_Operand.m_Handle);
	//}

	void VM::call(const Command cmd)
	{
		using enum EInstruction_t;

		switch (cmd.opcode)
		{
		case NONE:
			break;
		case BREAKPOINT:
			__debugbreak();
			break;

		case BIND_VERTEX_OBJECT:
			glBindVertexArray(cmd.operands[0].m_Handle);
			break;

		case BIND_VERTEX_BUFFER:
			glBindBuffer(GL_ARRAY_BUFFER, cmd.operands[0].m_Handle);
			break;

		case BIND_ELEMENT_BUFFER:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cmd.operands[0].m_Handle);
			break;

		case SET_CLEAR_COLOR:
			glClearColor(
				cmd.operands[0].m_Float,
				cmd.operands[1].m_Float,
				cmd.operands[2].m_Float,
				cmd.operands[3].m_Float
			);
			break;

		case CLEAR:
			glClear(cmd.operands[0].m_Flags);
			break;
		case DRAW_VERTEX_OBJECT:
			// enum, sizei, enum, void*
			glDrawElements(
				cmd.operands[0].m_Option,
				cmd.operands[1].m_Size,
				cmd.operands[2].m_Option,
				cmd.operands[3].m_Ptr
			);
			break;

		default:
			return;
		}
	}

}