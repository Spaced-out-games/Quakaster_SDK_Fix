#pragma once
#include "../Core.h"
#include "Entity.h"
#include "Scene.h"
#include <limits>


namespace qk
{

	
	/// <summary>
	/// Stores a table of children, with O(1) insertions, deletions, stable handles,
	/// and accessing children by name (free for constexpr names)
	/// </summary>
	class QK_API CActorTable
	{


		entt::registry& m_Registry;
		std::unordered_map<uint64_t, entt::entity> m_Children;
		entt::entity m_Root = entt::null;

		public:

			using key_t = uint64_t;



			/// <summary>
			/// 
			/// </summary>
			/// <param name="registry">the registry to add this Actor to</param>
			CActorTable(entt::registry& registry); // & ensures it actually exists


			/// <summary>
			/// Transfers ownership of a free entity to this Actor
			/// </summary>
			/// <param name="child">The ID of the loose child</param>
			/// <returns>a temporary view of the child</returns>
			//Entity add_child(key_t key, entt::entity child);

			/// <summary>
			/// Creates a new child entity
			/// </summary>
			/// <returns>a temporary view of the new child entity</returns>
			Entity add_child(key_t key);

			Entity operator[](key_t key);

			bool has_child(key_t key);

	};

	class QK_API AActor: public Entity
	{
		AActor(entt::registry& registry);

		inline bool has_child(CActorTable::key_t key);
		inline Entity operator[](CActorTable::key_t key);
		inline Entity add_child(CActorTable::key_t key);
		
	};

	inline bool isAActor(const Entity& target);
	
}