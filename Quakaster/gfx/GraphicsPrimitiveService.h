#pragma once
#include "VertexAttributeSetupRegistry.h"
#include "VertexBufferGenerator.h"
#include "../core.h"
#include "../core/IService.h"
#include <unordered_map>
#include <entt/core/hashed_string.hpp>
#include "../core/Stopwatch.h"
#include <spdlog/spdlog.h>

namespace gfx {

	QK_API unsigned int make_vertexBuffer_impl();
	QK_API void bind_vertexBuffer_impl(unsigned int target);
	QK_API void upload_vertexBuffer_impl(const void* data, ptrdiff_t size, GLenum usage);
	QK_API unsigned int compile_shader(unsigned int type, const char* src);
	QK_API unsigned int create_shader_program(const char* vertSrc, const char* fragSrc);
	QK_API void bind_shader_program(unsigned int program);
	QK_API void drawArrays(unsigned int mode, int first, int count);
	QK_API unsigned int generate_vao();
	QK_API void bind_vao(unsigned int vao);


	class QK_API GraphicsPrimitiveService : public qk::IService, public VertexAttributeSetupRegistry {


		std::unordered_map<entt::id_type, VertexBufferGenerator> m_VertexBufferGenerators;


		public:
			GraphicsPrimitiveService() = default;
			//VertexAttributeSetupRegistry m_AttributeSetupRegistry;

			template <typename vertex_t>
			void add_generator(entt::hashed_string name) {
				m_VertexBufferGenerators[name.value()].type = typeid(vertex_t);
				m_VertexBufferGenerators[name.value()].impl = [](const void* data, size_t size, unsigned int usage) -> unsigned int {
					unsigned int result = make_vertexBuffer_impl();
					bind_vertexBuffer_impl(result);
					upload_vertexBuffer_impl(data, size, usage);
					bind_vertexBuffer_impl(0);
					return result;
				};
			}

			template <class vertex_t>
			unsigned int generate_vbo(entt::hashed_string archetype_id, const std::vector<vertex_t>& vertices, unsigned int usage) {
				
				if (!m_VertexBufferGenerators.contains(archetype_id.value())) {
					spdlog::warn("VertexBufferGenerator '{}' not found", archetype_id.data());
					return 0;
				}

				VertexBufferGenerator& generator = m_VertexBufferGenerators[archetype_id.value()];

				if (generator.type != typeid(vertex_t)) {
					spdlog::warn("VertexBufferGenerator '{}' type mismatch", archetype_id.data());
					return 0;
				}

				unsigned int vbo = generator(vertices.data(), vertices.size() * sizeof(vertex_t), usage);
				gfx::bind_vertexBuffer_impl(vbo);
				unsigned int location = 0;
				// calls m_SetupRegistry to set up vertex pointers
				registry()[typeid(vertex_t)](location, false, 0);
				return vbo;

			}




	};

}
