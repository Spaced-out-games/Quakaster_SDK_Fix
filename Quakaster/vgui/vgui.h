#pragma once
#include "../core/utility/Service.h"
#include "../core/io/ILayer.h"
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

namespace vgui {

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
	const std::string vert_shader = R"(
		#version 330 core

		layout(location = 0) in vec2 aPos;
		layout(location = 1) in vec2 aUV;
		layout(location = 2) in vec4 aColor;

		out vec2 vUV;
		out vec4 vColor;

		

		void main()
		{
			vUV = aUV;
			vColor = aColor;
			gl_Position = vec4(aPos, 0.0, 1.0);
		}
	)";
	const std::string frag_shader = R"(
		#version 330 core

		in vec2 vUV;
		in vec4 vColor;

		out vec4 FragColor;

		uniform sampler2D uTexture;

		void main()
		{
			vec4 tex = texture(uTexture, vUV);
			FragColor = tex * vColor;
		}
	)";

	class QK_API Layer2D : qk::IService, public qk::ILayer {
		std::vector<Vertex>		m_VertexBufferContents;
		std::vector<uint32_t>	m_IndexBufferContents;
		std::vector<DrawCmd>	m_CommandBuffer;
		gfx::VertexArray		m_VertexArray;
		gfx::IndexBuffer<uint32_t>		m_IndexBuffer;
		gfx::VertexBuffer<Vertex> m_VertexBuffer;
		gfx::ShaderProgram				m_Shader;
		uint32_t m_PrimitiveStartVertex = 0;
		uint32_t m_PrimitiveStartIndex = 0;
		bool   m_primitiveActive = false;
		// whether or not to clear the layer after every draw call
		public:
			Layer2D(uint32_t size);
			virtual ~Layer2D() override = default;
			void primitive_begin(gfx::Handle texture = gfx::NULL_HANDLE);

			void add_vertex(glm::vec2 position, glm::vec2 uv, glm::vec4 color);
			void add_index(uint32_t index);
			void primitive_end();

			EBlock on_event(const qk::Event& evt) override;

			void on_render() override;

			uint32_t vertex_count() const;
			bool					m_Persist = false; // hide this!

	};

	
	

	inline void draw_triangle(
		vgui::Layer2D& layer,
		glm::vec2 a,
		glm::vec2 b,
		glm::vec2 c,
		glm::vec4 color)
	{
		layer.primitive_begin();

		size_t start = layer.vertex_count();

		layer.add_vertex(a, { 0,0 }, color);
		layer.add_vertex(b, { 0,0 }, color);
		layer.add_vertex(c, { 0,0 }, color);

		layer.add_index(start + 0);
		layer.add_index(start + 1);
		layer.add_index(start + 2);

		layer.primitive_end();
	}


	inline void draw_rect(
		vgui::Layer2D& layer,
		glm::vec2 pos,
		glm::vec2 size,
		glm::vec4 color)
	{
		layer.primitive_begin();

		size_t start = layer.vertex_count();

		glm::vec2 p0 = pos;
		glm::vec2 p1 = pos + glm::vec2(size.x, 0);
		glm::vec2 p2 = pos + size;
		glm::vec2 p3 = pos + glm::vec2(0, size.y);

		layer.add_vertex(p0, { 0,0 }, color);
		layer.add_vertex(p1, { 1,0 }, color);
		layer.add_vertex(p2, { 1,1 }, color);
		layer.add_vertex(p3, { 0,1 }, color);

		layer.add_index(start + 0);
		layer.add_index(start + 1);
		layer.add_index(start + 2);

		layer.add_index(start + 0);
		layer.add_index(start + 2);
		layer.add_index(start + 3);

		layer.primitive_end();
	}

	void draw_image(
		vgui::Layer2D& layer,
		gfx::Handle texture,
		glm::vec2 pos,
		glm::vec2 size)
	{
		layer.primitive_begin(texture);

		size_t start = layer.vertex_count();

		glm::vec2 p0 = pos;
		glm::vec2 p1 = pos + glm::vec2(size.x, 0);
		glm::vec2 p2 = pos + size;
		glm::vec2 p3 = pos + glm::vec2(0, size.y);

		layer.add_vertex(p0, { 0,0 }, { 1,1,1,1 });
		layer.add_vertex(p1, { 1,0 }, { 1,1,1,1 });
		layer.add_vertex(p2, { 1,1 }, { 1,1,1,1 });
		layer.add_vertex(p3, { 0,1 }, { 1,1,1,1 });

		layer.add_index(start + 0);
		layer.add_index(start + 1);
		layer.add_index(start + 2);

		layer.add_index(start + 0);
		layer.add_index(start + 2);
		layer.add_index(start + 3);

		layer.primitive_end();
	}


}