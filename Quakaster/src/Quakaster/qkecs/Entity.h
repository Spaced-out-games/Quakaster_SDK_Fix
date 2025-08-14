#pragma once
#include "Scene.h"


namespace qk
{
	class QK_API Entity
	{

		entt::entity m_ID;

		public:
		
		// creates an entity in the scene
		Entity(Scene& scene);

		// creates a null entity
		Entity();


		template <class component_t>
		bool has(const Scene& scene)
		{
			return scene.m_Registry.all_of<component_t>(m_ID);
		}

		template <class component_t>
		component_t& get(Scene& scene)
		{
			return scene.m_Registry.get<component_t>(m_ID);
		}

		template <class component_t, class ...arg_Ts>
		component_t& add(Scene& scene, arg_Ts&&... args)
		{
			return scene.m_Registry.emplace<component_t>(m_ID, std::forward<arg_Ts>(args)...);
		}

		inline void destroy(Scene& scene);




	};
}