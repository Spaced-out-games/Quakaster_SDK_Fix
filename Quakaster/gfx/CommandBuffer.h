#pragma once
#include "ShaderProgram.h"
#include "DrawCommand.h"
#include "CommandBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include <vector>
#include "../core.h"

namespace qk::gfx {

	struct CommandBuffer;

	void QK_API call(const CommandBuffer& commandBuffer);


	class QK_API CommandBuffer {
		std::vector<DrawCommand> m_CommandBuffer;
		public:
			void bindVertexArray(const VertexArray& vertexarray);
			void bindTexture(const Texture& texture);
			void bindShaderProgram(const ShaderProgram& program);
			void drawVertexArray(PrimitiveType primitive_t, unsigned int first, unsigned int count);
			size_t size() const;
			const DrawCommand& at(size_t index) const;
	};

}