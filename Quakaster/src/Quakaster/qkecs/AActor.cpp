#include "AActor.h"


namespace qk
{
	AActor::AActor(): m_Root(), m_Children() {}

	AActor::AActor(Scene& scene): m_Root(scene)
	{}

	void AActor::destroy_children(Scene& scene)
	{
		for (auto& child: m_Children)
		{
			child.second.destroy(scene);
		}
		m_Children.clear();
	}
	void AActor::destroy(Scene& scene)
	{
		m_Root.destroy(scene);

		destroy_children(scene);

	}

	Entity& AActor::root() { return m_Root; }
	Entity& AActor::child(child_handle_t handle) { return m_Children.at(handle); }

	child_handle_t AActor::add_child(Scene& scene)
	{
		for (;;)
		{

			// Here, we'd do overflow protection for m_NextChildIndex, but we'd just be setting it to zero, which no-oping does anyways


			if (m_Children.find(m_NextChildIndex) == m_Children.end())
			{
				m_Children[m_NextChildIndex] = Entity(scene);
				return m_NextChildIndex++;
			}

			m_NextChildIndex++;
		}
	}

	void AActor::delete_child(Scene& scene, child_handle_t handle)
	{
		m_Children.at(handle).destroy(scene);
		m_Children.erase(handle);
	}

}