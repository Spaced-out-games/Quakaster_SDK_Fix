#pragma once
#include "vgui.h"
#include "../gfx/gfx.h"
#include <cassert>

namespace vgui {

    Layer2D::Layer2D(uint32_t size) {
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


    }

    void Layer2D::primitive_begin(gfx::Handle texture) {
        // we just add a command
        m_CommandBuffer.emplace_back(texture, m_IndexBufferContents.size(), 0, m_VertexBufferContents.size());
    }

    void Layer2D::add_vertex(glm::vec2 position, glm::vec2 uv, glm::vec4 color) {
        m_VertexBufferContents.emplace_back(position, uv, color);
    }

    void Layer2D::add_index(uint32_t index) {
        m_IndexBufferContents.push_back(index);
    }

    void Layer2D::primitive_end() {
        // actually add the sizes
        DrawCmd& target = m_CommandBuffer.back();
        target.indexCount = m_IndexBufferContents.size() - target.startIndex;
        target.vertexCount = m_VertexBufferContents.size() - target.startVertex;
    }

    qk::ILayer::EBlock Layer2D::on_event(const qk::Event & evt) {
        return EBlock::Pass;
    }

    uint32_t Layer2D::vertex_count() const {
        return m_VertexBufferContents.size();
    }


    void Layer2D::on_render()
    {
        if (m_CommandBuffer.empty())
            return;

        m_Shader.bind();
        m_VertexArray.bind();

        m_VertexBuffer.bind();
        m_IndexBuffer.bind();

        // Upload buffers
        m_VertexBuffer.upload(
            m_VertexBufferContents.data(),
            m_VertexBufferContents.size() * sizeof(Vertex),
            GL_DYNAMIC_DRAW
        );

        m_IndexBuffer.upload(
            m_IndexBufferContents.data(),
            m_IndexBufferContents.size() * sizeof(uint32_t)
        );

        for (const DrawCmd& cmd : m_CommandBuffer)
        {
            if (cmd.texture != gfx::NULL_HANDLE)
                glBindTexture(GL_TEXTURE_2D, cmd.texture);

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

} // namespace vgui