#include "MeshConfig.h"
#include "GL/glew.h"

namespace gfx {


    void add_vertex_attribute_pointer_impl(unsigned int& location, int num_components, unsigned int component_type, bool normalized, int stride, uintptr_t offset_bytes) {
        // don't forget this is called ahead of time, with VBO!!!
        //  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, num_components, component_type, normalized, stride, reinterpret_cast<const void*>(offset_bytes));
    }


    VBO MeshConfig::vbo(const void* data, ptrdiff_t size, unsigned int usage) {


        VBO result;

        if (!setup) {
            spdlog::error("MeshConfig setup is null");
            return result;
        }

        result.init();
        result.bind();
        result.upload(data, size, usage);

        unsigned int location = 0;
        setup(location, false, 0);   // call your attribute setup lambda

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return result;
    }


    void MeshGroup::ctor() {
        vao.init();
    }
    void MeshGroup::dtor() {
        vao.destroy();

    }
    void MeshGroup::bind() {
        vao.bind();
    }




}