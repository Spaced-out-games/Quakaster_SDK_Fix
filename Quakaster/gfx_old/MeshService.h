#pragma once
#include "entt/core/hashed_string.hpp"
#include "../core/IService.h"
#include "../core.h"
#include <typeindex>
#include "MeshGroup.h"
#include <unordered_map>
#include <type_traits>
#include <utility>
#include <boost/pfr.hpp>
namespace gfx {

	template<typename T>
	constexpr bool is_arithmetic_or_enum_v =
		std::is_arithmetic_v<std::remove_cvref_t<T>> ||
		std::is_enum_v<std::remove_cvref_t<T>>;

	class QK_API MeshService : public qk::IService {
		std::unordered_map<std::type_index, attribute_setup_pfn> m_SetupFuncs;
		std::vector<MeshGroup>									 m_Groups;
		std::unordered_map<entt::id_type, uint32_t>				m_GroupLUT;
		

		


		public:

			/// <summary>
			/// Registers a function that handles registration for a sole primitive_t.
			/// </summary>
			template <class primitive_t>
			bool register_primitive_setup(attribute_setup_pfn fn) {
				static_assert(is_arithmetic_or_enum_v<primitive_t>(), "primitive_t must be an arithmetic type");
				m_SetupFuncs[typeid(primitive_t)] = fn;
			}
			/// <summary>
			/// Registers an intermediate type
			/// </summary>
			template <class intermediate_t>
			bool register_intermediate_setup(attribute_setup_pfn fn) {
				static_assert(!is_arithmetic_or_enum_v<intermediate_t>(), "intermediate_t cannot be an arithmetic type");
				m_SetupFuncs[typeid(intermediate_t)] = fn;
			}


			/// <summary>
			/// generates an aggregate type for you, using registered primitives and intermediates
			/// </summary>
			template <class aggregate_t>
			void generate_aggregate_setup() {
				static_assert(!is_arithmetic_or_enum_v<aggregate_t>(), "intermediate_t cannot be an arithmetic type");

				static_assert(std::is_aggregate_v<aggregate_t>(), "intermediate_t ust be aggregate type");

				// Don't override if already exists
				if (m_GroupLUT.contains(typeid(aggregate_t))) return;



				m_SetupFuncs[typeid(aggregate_t)] = [this](unsigned int& location, bool normalized, uintptr_t offset) {

					aggregate_t vertex{}; // default instance for PFR

					boost::pfr::for_each_field(vertex, [&](const auto& field) {

						using FieldT = std::decay_t<decltype(field)>;

					if (this->m_SetupFuncs.contains(typeid(FieldT))) {
						this->m_SetupFuncs[typeid(FieldT)](location, normalized, offset); // recursive call
					}
					else {
						throw std::runtime_error("Unregistered field type for vertex attribute");
					}
					offset += ((uintptr_t)&field - (uintptr_t)&vertex);
					});

				};

			}

			/// <summary>
			/// Bypasses automatically generated setup functions.
			/// </summary>
			template <class aggregate_t>
			bool register_aggregate_setup_override(attribute_setup_pfn fn) {

				m_SetupFuncs[typeid(aggregate_t)] = fn;

			}

			template <class vertex_t>
			bool CreateMeshGroup(entt::hashed_string id) {
				if (!m_SetupFuncs.contains(typeid(vertex_t))) return false;

				//m_GroupLUT[id.value()] = m_Groups.size();
				//m_Groups.emplace(m_SetupFuncs.at(typeid(vertex_t)), typeid(vertex_t));


				return true;
			}

			MeshGroup* GetMeshGroup(entt::hashed_string id);
			MeshService();
			~MeshService();
	};

}