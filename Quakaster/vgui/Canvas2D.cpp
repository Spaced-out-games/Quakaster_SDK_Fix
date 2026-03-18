#pragma once
#include "Canvas2D.h"
#include "../gfx/gfx.h"
#include <cassert>

namespace qk::vgui {

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

			float x = (aPos.x / 1080.0) * 2.0 - 1.0;
			float y = 1.0 - (aPos.y / 1920.0) * 2.0;

			gl_Position = vec4(x, y, 0.0, 1.0);
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



    Canvas2D::Canvas2D(uint32_t size) {
        m_VertexBufferContents.reserve(size);
        m_IndexBufferContents.reserve(size);
        m_CommandBuffer.reserve(size);

        // initialize everything
        m_VertexArray.init();
        m_VertexArray.bind();
        
        m_VertexBuffer.init();
        m_VertexBuffer.bind();

        m_IndexBuffer.init();
        m_IndexBuffer.bind();

        // set up the vertex attributes
        gfx::VertexBufferLayout layout;

        layout.push<float>(2);
        layout.push<float>(2);
        layout.push<float>(4);
        m_VertexArray.apply(m_VertexBuffer, layout);

        gfx::Shader vert(vert_shader, GL_VERTEX_SHADER);
        gfx::Shader frag(frag_shader, GL_FRAGMENT_SHADER);

        m_Shader.init(frag.compile(), vert.compile());
        Image img;
        make_image(img, 1, 1, 4);
        auto* pPixel = (uint32_t*)(img.data());

        *pPixel = (uint32_t)0xffffffff;

        m_WhiteTex.init(img, GL_TEXTURE_2D);

        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    }

    void Canvas2D::primitive_begin(gfx::Handle texture) {
        // we just add a command
        m_CommandBuffer.emplace_back(
            texture,
            m_VertexBufferContents.size(),  // startVertex
            0,
            m_IndexBufferContents.size(),   // startIndex
            0
        );
    }

    void Canvas2D::add_vertex(glm::vec2 position, glm::vec2 uv, glm::vec4 color) {
        m_VertexBufferContents.emplace_back(position, uv, color);
    }

    void Canvas2D::add_index(uint32_t index) {
        m_IndexBufferContents.push_back(index);
    }

    void Canvas2D::primitive_end() {
        // actually add the sizes
        DrawCmd& target = m_CommandBuffer.back();
        target.indexCount = m_IndexBufferContents.size() - target.startIndex;
        target.vertexCount = m_VertexBufferContents.size() - target.startVertex;
    }

    Layer::EBlock Canvas2D::on_event(const Event& evt) {
        return EBlock::Pass;
    }

    uint32_t Canvas2D::vertex_count() const {
        return m_VertexBufferContents.size();
    }


    void Canvas2D::on_render()
    {
        if (m_CommandBuffer.empty())
            return;
        assert(m_IndexBufferContents.size() <= m_IndexBufferContents.capacity());
        assert(m_VertexBufferContents.size() <= m_VertexBufferContents.capacity());
        m_Shader.bind();
        //glUniform1i(glGetUniformLocation(m_Shader.handle(), "uTexture"), 0);
        m_VertexArray.bind();

        m_VertexBuffer.bind();
        m_IndexBuffer.bind();

        // Upload buffers
        m_VertexBuffer.upload(
            m_VertexBufferContents.data(),
            m_VertexBufferContents.size(),// * sizeof(Vertex),
            GL_DYNAMIC_DRAW
        );

        m_IndexBuffer.upload(
            m_IndexBufferContents.data(),
            m_IndexBufferContents.size()//, * sizeof(uint32_t)
        ); // error happens during this call

        glActiveTexture(GL_TEXTURE0);


        for (const DrawCmd& cmd : m_CommandBuffer)
        {
            assert(cmd.startIndex + cmd.indexCount <= m_IndexBufferContents.size());
            assert(cmd.startVertex + cmd.vertexCount <= m_VertexBufferContents.size());
            if (cmd.texture != gfx::NULL_HANDLE)
                glBindTexture(GL_TEXTURE_2D, cmd.texture);
            else {
                glBindTexture(GL_TEXTURE_2D, m_WhiteTex.handle());
            }



            glDrawElements(
                GL_TRIANGLES,
                cmd.indexCount,
                GL_UNSIGNED_INT,
                (void*)(cmd.startIndex * sizeof(uint32_t))
            );
        }

        if (!m_Persist)
        {
            m_VertexBufferContents.clear();
            m_IndexBufferContents.clear();
            m_CommandBuffer.clear();
        }
    }

    void Canvas2D::on_attach() {

    }

    void Canvas2D::on_detach() {

    }


    void Canvas2D::draw_triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec4 color) {
        primitive_begin();

        size_t start = vertex_count();

        add_vertex(a, { 0,0 }, color);
        add_vertex(b, { 0,0 }, color);
        add_vertex(c, { 0,0 }, color);

        add_index(0);
        add_index(1);
        add_index(2);

        primitive_end();
    }


    void Canvas2D::draw_rect(glm::vec2 pos, glm::vec2 size, glm::vec4 color)
    {
        primitive_begin();

        size_t start = vertex_count();

        glm::vec2 p0 = pos;
        glm::vec2 p1 = pos + glm::vec2(size.x, 0);
        glm::vec2 p2 = pos + size;
        glm::vec2 p3 = pos + glm::vec2(0, size.y);

        add_vertex(p0, { 0,1 }, color);
        add_vertex(p1, { 1,1 }, color);
        add_vertex(p2, { 1,0 }, color);
        add_vertex(p3, { 0,0 }, color);

        add_index(start + 0);
        add_index(start + 1);
        add_index(start + 2);

        add_index(start + 0);
        add_index(start + 2);
        add_index(start + 3);

        primitive_end();
    }

    void Canvas2D::draw_image(gfx::Handle texture, glm::vec2 pos, glm::vec2 size)
    {
        primitive_begin(texture);

        size_t start = vertex_count();

        glm::vec2 p0 = pos;
        glm::vec2 p1 = pos + glm::vec2(size.x, 0);
        glm::vec2 p2 = pos + size;
        glm::vec2 p3 = pos + glm::vec2(0, size.y);

        add_vertex(p0, { 0,0 }, { 1,1,1,1 });
        add_vertex(p1, { 1,0 }, { 1,1,1,1 });
        add_vertex(p2, { 1,1 }, { 1,1,1,1 });
        add_vertex(p3, { 0,1 }, { 1,1,1,1 });

        add_index(start + 0);
        add_index(start + 1);
        add_index(start + 2);

        add_index(start + 0);
        add_index(start + 2);
        add_index(start + 3);

        primitive_end();
    }

    void Canvas2D::draw_polygon(const glm::vec2* points, size_t count, glm::vec4 color)
    {
        assert(count >= 3 && "Polygon must have at least 3 points");

        primitive_begin();

        size_t start = vertex_count();

        
        for (size_t i = 0; i < count; ++i)
        {
            add_vertex(points[i], { 0,0 }, color);
        }

        
        for (size_t i = 1; i < count - 1; ++i)
        {
            add_index(start + 0);
            add_index(start + i);
            add_index(start + i + 1);
        }

        primitive_end();
    }




} // namespace vgui