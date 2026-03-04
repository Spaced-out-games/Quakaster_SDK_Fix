#pragma once
#include <typeindex>
#include "spdlog/spdlog.h"
#include "VAO.h"
#include "VBO.h"

namespace gfx {

    using attribute_setup_pfn = void(*)(unsigned int&, bool, uintptr_t);

    void QK_API add_vertex_attribute_pointer_impl(unsigned int& location, int num_components, unsigned int component_type, bool normalized, int stride, uintptr_t offset_bytes);


	struct QK_API MeshConfig {
        VBO vbo(const void* data, ptrdiff_t size, unsigned int usage);
        attribute_setup_pfn   setup = nullptr;
        std::type_index m_VertexType = typeid(void);


        MeshConfig() = default;
        ~MeshConfig() = default;



        //public:

        template <class vertex_t>
        VBO generate_vbo(const vertex_t* data, size_t count, unsigned int usage) {
            if (typeid(vertex_t) != m_VertexType) {
                spdlog::error("MeshConfig at {:#x}: Invalid type. Expected `{}`, got `{}`",
                    (uintptr_t)this, m_VertexType.name(), typeid(vertex_t).name());
                return VBO{};
            }
            return vbo(data, count * sizeof(vertex_t), usage);  // make sure size is in bytes
        }
	};

    struct QK_API MeshGroup {
        MeshConfig m_Config;
        VAO vao;


        template <class vertex_t>
        VBO generate_vbo(const vertex_t* data, size_t count, unsigned int usage) {
            return m_Config.generate_vbo(data, count, usage);
        }


        void ctor();
        void dtor();
        void bind();

    };

}