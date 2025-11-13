#pragma once
#include <GL/glew.h>
#include <stdint.h>
#include "../Core.h"
#include <string>
#include <format>


// probably should define these in their own headers eventually.

namespace qk::gfx
{
	// Opcode
	enum class EInstruction_t : uint64_t
	{
		NONE,
		BREAKPOINT,
		SET_R0,
		SET_R1,
		SET_R2,
		SET_R3,
		BIND_VERTEX_OBJECT,
		BIND_VERTEX_BUFFER,
		BIND_ELEMENT_BUFFER,
		SET_CLEAR_COLOR,
		CLEAR,
		DRAW_VERTEX_OBJECT

	};

	const char* to_string(EInstruction_t opcode)
	{
		using enum EInstruction_t;


		switch (opcode)
		{
		case NONE:
			return "NONE";
		case SET_R0:
			return "SET_R0";
		case SET_R1:
			return "SET_R1";
		case SET_R2:
			return "SET_R2";
		case SET_R3:
			return "SET_R3";
		case BIND_VERTEX_OBJECT:
			return "BIND_VERTEX_OBJECT";
		case BIND_VERTEX_BUFFER:
			return "BIND_VERTEX_BUFFER";
		case BIND_ELEMENT_BUFFER:
			return "BIND_ELEMENT_BUFFER";
		case SET_CLEAR_COLOR:
			return "SET_CLEAR_COLOR";
		case CLEAR:
			return "CLEAR";
		default:
			return "<unknown>";
		}
	}


	// Represents a number or handle.
	union EOperand_t
	{
		// Floating point value
		float		m_Float;

		int			m_Int;

		// Represents an OpenGL handle
		GLuint		m_Handle;

		// Represents an OpenGL option
		GLenum		m_Option;

		// Represents OpenGL mask
		GLbitfield	m_Flags;

		// OpenGL size type
		GLsizei		m_Size;

		// 
		const void* m_Ptr = {};
	};

	// TODO: FIND A WAY TO SHRINK

	// Represents an assembly instruction for the interpreter
	struct Command
	{
		EInstruction_t opcode;
		EOperand_t	   operands[7];

	};


	// Converts an Instruction to a string
	std::string to_string(Command cmd)
	{

		return std::format("{}\t\t{}\t\t{}\t\t{}\t\t{};",
			to_string(cmd.opcode),
			cmd.operands[0].m_Handle,
			cmd.operands[1].m_Handle,
			cmd.operands[2].m_Handle,
			cmd.operands[3].m_Handle
		);
	}


	struct RenderPass
	{
		std::vector<Command> m_Commands;

		std::string to_string()
		{
			std::string result = "";

			for (auto& cmd : m_Commands)
				result += std::format("{}\n", qk::gfx::to_string(cmd));
			
			return result;
		}


		inline RenderPass& set_clear_color(float r, float g, float b, float a)
		{
			Command cmd;
			cmd.opcode = EInstruction_t::SET_CLEAR_COLOR;
			cmd.operands[0].m_Float = r;
			cmd.operands[1].m_Float = g;
			cmd.operands[2].m_Float = b;
			cmd.operands[3].m_Float = a;
			m_Commands.push_back(cmd);
			return *this;
		}

		inline RenderPass& clear(GLbitfield flags)
		{
			Command cmd;
			cmd.opcode = EInstruction_t::CLEAR;
			cmd.operands[0].m_Flags = flags;
			m_Commands.push_back(cmd);
			return *this;
		}

		inline RenderPass& bind_vertex_object(GLuint vao)
		{
			Command cmd;
			cmd.opcode = EInstruction_t::BIND_VERTEX_OBJECT;
			cmd.operands[0].m_Handle = vao;
			m_Commands.push_back(cmd);
			return *this;
		}

		inline RenderPass& bind_vertex_buffer(GLuint vbo)
		{
			Command cmd;
			cmd.opcode = EInstruction_t::BIND_VERTEX_BUFFER;
			cmd.operands[0].m_Handle = vbo;
			m_Commands.push_back(cmd);
			return *this;
		}

		inline RenderPass& bind_element_buffer(GLuint ebo)
		{
			Command cmd;
			cmd.opcode = EInstruction_t::BIND_ELEMENT_BUFFER;
			cmd.operands[0].m_Handle = ebo;
			m_Commands.push_back(cmd);
			return *this;
		}

		inline RenderPass& draw_vertex_object(GLenum mode, GLsizei count, GLenum type, const void* indices)
		{
			Command cmd;
			cmd.opcode = EInstruction_t::DRAW_VERTEX_OBJECT;
			cmd.operands[0].m_Option = mode;
			cmd.operands[1].m_Size = count;
			cmd.operands[2].m_Option = type;
			cmd.operands[3].m_Ptr = indices;
			m_Commands.push_back(cmd);
			return *this;
		}

	};

	


	// Represents a virtual machine that runs Instructions
	struct QK_API VM
	{

		// needs to stay non-inline so that 
		void call(const Command cmd);

		inline void call(RenderPass* rp)
		{
			if (rp)
			{
				for (const auto& cmd: rp->m_Commands)
				{
					call(cmd);
				}
			}
		}

	};


}