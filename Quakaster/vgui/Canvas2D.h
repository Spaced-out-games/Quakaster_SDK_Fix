#pragma once
#include "../core/utility/Service.h"
#include "../core/io/Layer.h"
#include "../gfx/VertexBufferLayout.h"
#include "../gfx/VertexBuffer.h"
#include "../gfx/VertexArray.h"
#include "../gfx/IndexBuffer.h"
#include "../gfx/Shader.h"
#include "../gfx/ShaderProgram.h"
#include "../gfx/Texture.h"
#include "../gfx/types.h"
#include "../core.h"
#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

using namespace qk::io;
using namespace qk::resource;
using namespace qk;

namespace qk::vgui {

	struct Vertex {
		glm::vec2 position = {0.0,0.0};
		glm::vec2 uv = { 0.0,0.0 };
		glm::vec4 color = { 1.0, 1.0, 1.0, 1.0 }; // supports transparency I guess
	};

	struct DrawCmd {
		gfx::Handle texture = gfx::NULL_HANDLE;
		size_t startVertex = 0;
		size_t vertexCount = 0;
		size_t startIndex = 0;
		size_t indexCount = 0;
	};


	
	//DESIGN: Store a vertex buffer and an index buffer. Each primitive just pushes to both. We obviously procedurally generate vertices for
	//images based on provided xywh. We take a Texture&, get the handle, and put it in the DrawCmd. Each DrawCmd represents one primitive
	//and stores the related state for that call. To render, we iterate and use these to capture a subset of both the vertex buffer and the
	//index buffer, and draw that, respecting texture bindings beforehand.

	//We aggregate 
	

	// for now


	class QK_API Canvas2D : util::IService, public Layer {
		std::vector<Vertex>		m_VertexBufferContents;
		std::vector<uint32_t>	m_IndexBufferContents;
		std::vector<DrawCmd>	m_CommandBuffer;
		gfx::VertexArray		m_VertexArray;
		gfx::IndexBuffer<uint32_t>		m_IndexBuffer;
		gfx::VertexBuffer<Vertex> m_VertexBuffer;
		gfx::ShaderProgram				m_Shader;
		gfx::Texture					m_WhiteTex;
		uint32_t m_PrimitiveStartVertex = 0;
		uint32_t m_PrimitiveStartIndex = 0;
		bool   m_primitiveActive = false;
		// whether or not to clear the layer after every draw call
		public:
			Canvas2D(uint32_t size);
			virtual ~Canvas2D() override = default;
			void primitive_begin(gfx::Handle texture = gfx::NULL_HANDLE);

			void add_vertex(glm::vec2 position, glm::vec2 uv, glm::vec4 color);
			void add_index(uint32_t index);
			void primitive_end();

			EBlock on_event(const Event& evt) override;

			void on_render() override;

			void on_attach() override;

			void on_detach() override;



			uint32_t vertex_count() const;
			bool					m_Persist = false; // hide this!

			inline void draw_triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec4 color);

			inline void draw_rect(glm::vec2 pos, glm::vec2 size, glm::vec4 color);

			inline void draw_image(gfx::Handle texture, glm::vec2 pos, glm::vec2 size);

			inline void draw_polygon(const glm::vec2* points, size_t count, glm::vec4 color);
	};

	
	

	


}