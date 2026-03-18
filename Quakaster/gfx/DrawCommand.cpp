#include "DrawCommand.h"
#include "GL/glew.h"

namespace qk::gfx {

	void call(const DrawCommand& command) {
		using enum ECommandType;
		switch (command.type)
		{
		case BIND_VERTEXARRAY:
			glBindVertexArray(command.handles[0]);
			break;
		case BIND_VERTEXBUFFER:
			glBindBuffer(GL_ARRAY_BUFFER, command.handles[0]);
			break;

		case BIND_INDEXBUFFER:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, command.handles[0]);
			break;

		case BIND_TEXTURE:
			glBindTexture(command.handles[1], command.handles[0]);
			break;

		case BIND_SHADER:
			glUseProgram(command.handles[0]);
			break;

		case DRAW_VERTEXARRAY:
			glDrawArrays(command.handles[0], command.handles[1], command.handles[2]);
			break;

		default:
			break;
		}

	}

}