#pragma once
#include "boost/pfr.hpp"
#include <unordered_map>
#include <typeindex>
#include "../core.h"

#define GFX_INIT_PRIMITIVE_ATTRIBUTES(reg) \
	reg.autoregister_vertex_attribute_setup_override<float>([](unsigned int& location, bool normalize, uintptr_t offset) { \
		gfx::add_vertex_attribute_pointer_impl(location, 1, GL_FLOAT, normalize, sizeof(float), offset); location++; \
	}); \
	reg.autoregister_vertex_attribute_setup_override<int>([](unsigned int& location, bool normalize, uintptr_t offset) { \
		gfx::add_vertex_attribute_pointer_impl(location, 1, GL_INT, normalize, sizeof(int), offset); location++; \
	}); \
	reg.autoregister_vertex_attribute_setup_override<unsigned int>([](unsigned int& location, bool normalize, uintptr_t offset) { \
		gfx::add_vertex_attribute_pointer_impl(location, 1, GL_UNSIGNED_INT, normalize, sizeof(unsigned int), offset); location++; \
	}); \
	reg.autoregister_vertex_attribute_setup_override<glm::vec2>([](unsigned int& location, bool normalize, uintptr_t offset) { \
		gfx::add_vertex_attribute_pointer_impl(location, 2, GL_FLOAT, normalize, sizeof(float), offset); location++; \
	}); \
	reg.autoregister_vertex_attribute_setup_override<glm::vec3>([](unsigned int& location, bool normalize, uintptr_t offset) { \
		gfx::add_vertex_attribute_pointer_impl(location, 3, GL_FLOAT, normalize, sizeof(float), offset); location++; \
	}); \
	reg.autoregister_vertex_attribute_setup_override<glm::vec4>([](unsigned int& location, bool normalize, uintptr_t offset) { \
		gfx::add_vertex_attribute_pointer_impl(location, 4, GL_FLOAT, normalize, sizeof(float), offset); location++; \
	}); \
	reg.autoregister_vertex_attribute_setup_override<glm::mat4>([](unsigned int& location, bool normalize, uintptr_t offset) { \
		gfx::add_vertex_attribute_pointer_impl(location, 4, GL_FLOAT, normalize, sizeof(float), offset); location++; \
		gfx::add_vertex_attribute_pointer_impl(location, 4, GL_FLOAT, normalize, sizeof(float), offset); location++; \
		gfx::add_vertex_attribute_pointer_impl(location, 4, GL_FLOAT, normalize, sizeof(float), offset); location++; \
		gfx::add_vertex_attribute_pointer_impl(location, 4, GL_FLOAT, normalize, sizeof(float), offset); location++; \
	}) \


namespace gfx {

	// Adds a single vertex attribute pointer.
	void QK_API add_vertex_attribute_pointer_impl(unsigned int& location, int num_components, unsigned int component_type, bool normalized, int stride, uintptr_t offset_bytes);

	// manages micro-lambdas for vertex attribute setup
	class QK_API VertexAttributeSetupRegistry {

		//  has to be captured ¯\_(ツ)_/¯
		using setup_lambda_t = std::function<void(unsigned int& location, bool normalized, uintptr_t offset)>;
		


		// Maps a type to a lambda that calls add_vertex_attribute_pointer_impl() OR an auto-generated lambda that registers aggregates
		std::unordered_map<std::type_index, setup_lambda_t> m_SetupRegistry;
		
		public:

			std::unordered_map<std::type_index, setup_lambda_t>& registry();

			// Allows you to manually define a lambda to set up your vertex_t (and primitives!)
			template <class vertex_t>
			void autogen_attribute_setup_override(setup_lambda_t lambda) {
				m_SetupRegistry[typeid(vertex_t)] = lambda;
			}

			// Generates a lambda to set up your vertex_t
			template <class vertex_t>
			void autogen_attribute_setup() {

				static_assert(std::is_aggregate_v<vertex_t>(), "Must be aggregate type");

				// Don't override if already exists
				if (m_SetupRegistry.contains(typeid(vertex_t))) return;

				m_SetupRegistry[typeid(vertex_t)] = [&m_SetupRegistry](unsigned int& location, bool normalized, uintptr_t offset) {

					vertex_t vertex{}; // default instance for PFR

					boost::pfr::for_each_field(vertex, [&](const auto& field) {
						
						using FieldT = std::decay_t<decltype(field)>;

					if (m_SetupRegistry.contains(typeid(FieldT))) {
						m_SetupRegistry[typeid(FieldT)](location, normalized, offset); // recursive call
					}
					else {
						throw std::runtime_error("Unregistered field type for vertex attribute");
					}
					offset += ((uintptr_t)&field - (uintptr_t)&vertex);
					});

				};

			}

	};



}