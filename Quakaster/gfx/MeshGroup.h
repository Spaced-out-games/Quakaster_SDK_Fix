#pragma once
#include <typeindex>
#include "spdlog/spdlog.h"
#include "VAO.h"
#include "VBO.h"

namespace gfx {

    using attribute_setup_pfn = std::function<void(unsigned int&, bool, uintptr_t)>;

    void QK_API drawArrays(unsigned int mode, int first, int count);

    void QK_API add_vertex_attribute_pointer_impl(unsigned int& location, int num_components, unsigned int component_type, bool normalized, int stride, uintptr_t offset_bytes);




    struct QK_API MeshGroup {

        friend class MeshService;

        VBO vbo(const void* data, ptrdiff_t size, unsigned int usage);
        //MeshConfig m_Config;
        std::type_index         m_VertexType = typeid(void);
        attribute_setup_pfn     m_Setup_pfn = nullptr;
        VAO vao;

        MeshGroup(attribute_setup_pfn setup, std::type_index type);

    public:
        template <class vertex_t>
        VBO generate_vbo(const vertex_t* data, size_t count, unsigned int usage) {
            if (typeid(vertex_t) != m_VertexType) {
                spdlog::error("MeshConfig at {:#x}: Invalid type. Expected `{}`, got `{}`",
                    (uintptr_t)this, m_VertexType.name(), typeid(vertex_t).name());
                return VBO{};
            }
            return vbo(data, count * sizeof(vertex_t), usage);  // make sure size is in bytes
        }

        void ctor();
        void dtor();
        void bind();

    };

}