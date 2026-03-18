#include "CommandBuffer.h"

namespace qk::gfx {

	void CommandBuffer::bindVertexArray(const VertexArray& vertexarray) {

		auto& command = m_CommandBuffer.emplace_back();
		command.type = ECommandType::BIND_VERTEXARRAY;
		command.handles[0] = vertexarray.handle();

	}
	void CommandBuffer::bindTexture(const Texture& texture) {

		auto& command = m_CommandBuffer.emplace_back();
		command.type = ECommandType::BIND_TEXTURE;
		command.handles[0] = texture.handle();
		command.handles[1] = texture.type();

	}
	void CommandBuffer::bindShaderProgram(const ShaderProgram& program) {

		auto& command = m_CommandBuffer.emplace_back();
		command.type = ECommandType::BIND_SHADER;
		command.handles[0] = program.handle();

	}
	void CommandBuffer::drawVertexArray(PrimitiveType primitive_t, unsigned int first, unsigned int count) {

		auto& command = m_CommandBuffer.emplace_back();
		command.type = ECommandType::DRAW_VERTEXARRAY;
		command.handles[0] = primitive_t;
		command.handles[1] = first;
		command.handles[2] = count;

	}
	size_t CommandBuffer::size() const {
		return m_CommandBuffer.size();
	}
	const DrawCommand& CommandBuffer::at(size_t index) const {
		return m_CommandBuffer.at(index);
	}

	void call(const CommandBuffer& commandBuffer) {
		for (size_t i = 0; i < commandBuffer.size(); i++) {
			call(commandBuffer.at(i));
		}
	}

}