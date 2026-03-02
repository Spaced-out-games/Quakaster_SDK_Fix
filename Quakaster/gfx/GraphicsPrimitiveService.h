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




	class QK_API GraphicsPrimitiveService : public qk::IService, public VertexAttributeSetupRegistry {


		std::unordered_map<entt::id_type, VertexBufferGenerator> m_VertexBufferGenerators;


		public:

			/*								Vertex Buffers								*/

			static void VBO_upload_impl(const void* data, ptrdiff_t size, GLenum usage);
			static void VBO_bind_impl(unsigned int target);
			static void VBO_dtor_impl(unsigned int target);
			static unsigned int VBO_ctor_impl();



			/*							Vertex Buffer Objectives							*/

			static void VAO_dtor_impl(unsigned int target);
			static void VAO_bind_impl(unsigned int vao);
			static unsigned int VAO_ctor_impl();



			/*							Shader Program							*/

			static unsigned int shader_program_ctor_impl(const char* vertSrc, const char* fragSrc);
			static unsigned int shader_compile_impl(unsigned int type, const char* src);
			static void			shader_program_bind_impl(unsigned int program);



			static void drawArrays(unsigned int mode, int first, int count);





			GraphicsPrimitiveService() = default;
			//VertexAttributeSetupRegistry m_AttributeSetupRegistry;

			template <typename vertex_t>
			void add_generator(entt::hashed_string VBO_generator_ID) {
				m_VertexBufferGenerators[VBO_generator_ID.value()].type = typeid(vertex_t);
				m_VertexBufferGenerators[VBO_generator_ID.value()].impl = [](const void* data, size_t size, unsigned int usage) -> unsigned int {
					unsigned int result = VBO_ctor_impl();
					VBO_bind_impl(result);
					VBO_upload_impl(data, size, usage);
					VBO_bind_impl(0);
					return result;
				};
			}

			template <class vertex_t>
			unsigned int generate_vbo(entt::hashed_string VBO_generator_ID, const std::vector<vertex_t>& vertices, unsigned int usage) {
				
				if (!m_VertexBufferGenerators.contains(VBO_generator_ID.value())) {
					spdlog::warn("VertexBufferGenerator '{}' not found", VBO_generator_ID.data());
					return 0;
				}

				VertexBufferGenerator& generator = m_VertexBufferGenerators[VBO_generator_ID.value()];

				if (generator.type != typeid(vertex_t)) {
					spdlog::warn("VertexBufferGenerator '{}' type mismatch", VBO_generator_ID.data());
					return 0;
				}

				unsigned int vbo = generator(vertices.data(), vertices.size() * sizeof(vertex_t), usage);
				VBO_bind_impl(vbo);
				unsigned int location = 0;
				// calls m_SetupRegistry to set up vertex pointers
				registry()[typeid(vertex_t)](location, false, 0);
				return vbo;

			}




	};

}
