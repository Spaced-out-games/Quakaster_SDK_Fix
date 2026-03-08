#include "MeshGroup.h"
#include "GL/glew.h"

namespace gfx {

    void drawArrays(unsigned int mode, int first, int count) {
        glDrawArrays(mode, first, (GLsizei)count);

    }


    void add_vertex_attribute_pointer_impl(unsigned int& location, int num_components, unsigned int component_type, bool normalized, int stride, uintptr_t offset_bytes) {
        // don't forget this is called ahead of time, with VBO!!!
        //  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, num_components, component_type, normalized, stride, reinterpret_cast<const void*>(offset_bytes));
    }


    VBO MeshGroup::vbo(const void* data, ptrdiff_t size, unsigned int usage) {


        VBO result;

        if (!m_Setup_pfn) {
            spdlog::error("MeshConfig setup is null");
            return result;
        }

        result.init();
        result.bind();
        result.upload(data, size, usage);

        unsigned int location = 0;
        // false and zero are fine here since it should be relative to an aggregate
        m_Setup_pfn(location, false, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return result;
    }

    MeshGroup::MeshGroup(MeshGroup&& other) noexcept
    : m_VertexType(other.m_VertexType),
      m_Setup_pfn(std::move(other.m_Setup_pfn)),
      vao(std::move(other.vao))
{}


    void MeshGroup::ctor() {
        vao.init();
    }
    void MeshGroup::dtor() {
        vao.destroy();

    }
    void MeshGroup::bind() {
        vao.bind();
    }

    MeshGroup::MeshGroup(attribute_setup_pfn setup, std::type_index type) :
        m_VertexType(type), m_Setup_pfn(setup) {
        vao.init();
    }




}