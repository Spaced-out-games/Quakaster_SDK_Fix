#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "../Core.h"
#include <GL/glew.h>
#include "../qk/QKTL.h"
#include <boost/pfr.hpp>
#include "../qkmath/mat4.h"
#include "../qkmath/vec3.h"
#include "../qkmath/vec2.h"
#include "../qkmath/vec4.h"
#include "../qkmath/quaternion.h"


namespace qk::gfx
{

	// Sets up a VAO
	using VAO_policy = func_ptr_t<void, void>;

	void QK_API add_int_pointer(GLuint& index, GLsizei stride, size_t offset);
	void QK_API add_float_pointer(GLuint& index, GLsizei stride, size_t offset);
	void QK_API add_vec2_pointer(GLuint& index, GLsizei stride, size_t offset);
	void QK_API add_vec3_pointer(GLuint& index, GLsizei stride, size_t offset);
	void QK_API add_vec4_pointer(GLuint& index, GLsizei stride, size_t offset);
	void QK_API add_mat4_pointer(GLuint& index, GLsizei stride, size_t offset);
	void QK_API add_quat_pointer(GLuint& index, GLsizei stride, size_t offset);
	void QK_API add_uint_pointer(GLuint& index, GLsizei stride, size_t offset);

	template <class vertex_t>
	VAO_policy make_VAO_policy()
	{
		return []()
		{
			GLuint attribute_index = 0;
			size_t offset = 0;
			vertex_t dummy{};

			boost::pfr::for_each_field(dummy, [&](const auto& field)
			{

				using field_t = std::decay_t<decltype(field)>;

				add_vertex_attribute<field_t>(attribute_index, sizeof(vertex_t), offset);

				offset += sizeof(field_t);

				++attribute_index;

			}
			);
		};
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
    void add_vertex_attribute<qk::vec2>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_vec2_pointer(index, stride, offset);

    }

    template <>
    void add_vertex_attribute<qk::vec3>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_vec3_pointer(index, stride, offset);

    }

    template <>
    void add_vertex_attribute<qk::vec4>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_vec4_pointer(index, stride, offset);

    }

    template <>
    void add_vertex_attribute<qk::quat>(GLuint& index, GLsizei stride, size_t offset)
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
    void add_vertex_attribute<qk::mat4>(GLuint& index, GLsizei stride, size_t offset)
    {
        add_mat4_pointer(index, stride, offset);
    }
}
