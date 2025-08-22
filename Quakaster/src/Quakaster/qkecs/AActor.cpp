#include "AActor.h"

namespace qk
{


	/// <summary>
	/// Stores a table of children, with O(1) insertions, deletions, stable handles,
	/// and accessing children by name (free for constexpr names)
	/// </summary>
	CActorTable::CActorTable(entt::registry& registry): m_Registry(registry), m_Root(m_Registry.create())
	{
	}

	Entity CActorTable::add_child(key_t key)
	{

		auto [iter, inserted] = m_Children.try_emplace(key, entt::null);
		if (inserted) {
			iter->second = m_Registry.create();
		}
		return Entity(m_Registry, iter->second);


		

	}

	Entity CActorTable::operator[](key_t key)
	{
		entt::entity target = entt::null;

		if (m_Children.find(key) != m_Children.end())
		{

			return Entity(m_Registry, m_Children.at(key));

		}
		__debugbreak();
		return Entity(m_Registry, entt::null);

	}

	bool CActorTable::has_child(key_t key)
	{
		return m_Children.find(key) != m_Children.end();
	}


	// AACTOR


	AActor::AActor(entt::registry& registry) : Entity(registry)
	{
		// inserted, per its definition
		emplace<CActorTable>(registry);
	}

	bool AActor::has_child(CActorTable::key_t key)
	{
		return get<CActorTable>().has_child(key);
	}

	Entity AActor::operator[](CActorTable::key_t key)
	{
		return get<CActorTable>()[key];
	}
	Entity AActor::add_child(CActorTable::key_t key)
	{
		return get<CActorTable>().add_child(key);
	}

	bool isAActor(const Entity& target)
	{
		return target.all_of<CActorTable>();
	}


}