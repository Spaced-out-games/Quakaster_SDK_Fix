#pragma once
#include "../../Core.h"
#include "../../qkmath/qkmath.h"
#include "gl_utils.h" // for debugging OpenGL calls
#include "VAO.h"
#include <boost/pfr.hpp>

namespace qkg
{

    void QK_API add_int_pointer(GLuint& index, GLsizei stride, size_t offset);
    void QK_API add_float_pointer(GLuint& index, GLsizei stride, size_t offset);
    void QK_API add_vec2_pointer(GLuint& index, GLsizei stride, size_t offset);
    void QK_API add_vec3_pointer(GLuint& index, GLsizei stride, size_t offset);
    void QK_API add_vec4_pointer(GLuint& index, GLsizei stride, size_t offset);
    void QK_API add_mat4_pointer(GLuint& index, GLsizei stride, size_t offset);
    void QK_API add_quat_pointer(GLuint& index, GLsizei stride, size_t offset);
    void QK_API add_uint_pointer(GLuint& index, GLsizei stride, size_t offset);
    // Stores a lambda for generating a VAO
    template <class vertex_t>
    class MeshConfiguration
    {
        func_ptr_t<void, void> m_Generator;

        public:
            MeshConfiguration();
            ~MeshConfiguration();
            void configure();
    };





    template <class vertex_t>
    MeshConfiguration<vertex_t>::MeshConfiguration() {
        
        // set the lambda

        m_Generator = [](void) -> void {

            vertex_t dummy{};
            GLuint attribute_index = 0;
            size_t offset = 0;

            boost::pfr::for_each_field(dummy, [&](const auto& field) {
                using field_t = std::decay_t<decltype(field)>;

                add_vertex_attribute<field_t>(attribute_index, sizeof(vertex_t), offset);

                offset += sizeof(field_t);

                ++attribute_index;
            });


        };

    }

    template <class vertex_t>
    MeshConfiguration<vertex_t>::~MeshConfiguration() {
        
    }

    

    template <class vertex_t>
    void MeshConfiguration<vertex_t>::configure()
    {
        if (m_Generator) m_Generator();
        else
        {
            __debugbreak();
        }
    }





    

    



    template <class component_t>
    void add_vertex_attribute(GLuint& index, GLsizei stride, size_t offset)
    {
        static_assert(sizeof(component_t) == 0, "Component type unsupported");
    }

    template <>
    void add_vertex_attribute<float>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_float_pointer(index, stride, offset);
    }

    template <>
    void add_vertex_attribute<vec2>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_vec2_pointer(index, stride, offset);

    }

    template <>
    void add_vertex_attribute<vec3>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_vec3_pointer(index, stride, offset);

    }

    template <>
    void add_vertex_attribute<vec4>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_vec4_pointer(index, stride, offset);

    }

    template <>
    void add_vertex_attribute<quat>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_quat_pointer(index, stride, offset);

    }

    template <>
    void add_vertex_attribute<int>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_int_pointer(index, stride, offset);

    }

    template <>
    void add_vertex_attribute<unsigned int>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_uint_pointer(index, stride, offset);

    }

    template <>
    void add_vertex_attribute<mat4>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_mat4_pointer(index, stride, offset);
    }

}