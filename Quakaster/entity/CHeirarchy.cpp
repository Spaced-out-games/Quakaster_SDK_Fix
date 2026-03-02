#include "CHeirarchy.h"
#include "../core/Stopwatch.h"

namespace qk::entity {


	CHeirarchyService::CHeirarchyService(entt::registry& target) : registry(target) {

	}

	entt::entity CHeirarchyService::find_highest_dirty_ancestor(entt::entity target) {
		entt::entity result = entt::null;
		entt::entity current = target;

		while (current != entt::null) {
			if (registry.all_of<CHeirarchy::DirtyFlag>(current))
				result = current;

			if (!registry.all_of<CHeirarchy>(current))
				break;

			current = registry.get<CHeirarchy>(current).parent;
		}

		return result;
	}

	entt::entity CHeirarchyService::find_lowest_dirty_ancestor(entt::entity target) {
		entt::entity current = target;

		while (current != entt::null) {
			if (registry.all_of<CHeirarchy::DirtyFlag>(current))
				return current;

			if (!registry.all_of<CHeirarchy>(current))
				break;

			current = registry.get<CHeirarchy>(current).parent;
		}

		return entt::null;
	}

	entt::entity CHeirarchyService::first(entt::entity target) {
		if (target == entt::null) return entt::null;

		entt::entity current = target;

		while (current != entt::null) {
			auto* h = registry.try_get<CHeirarchy>(current);
			if (!h) return entt::null;

			if (h->prev == entt::null)
				return current;

			current = h->prev;
		}

		return entt::null;
	}

	entt::entity CHeirarchyService::last(entt::entity target) {
		if (target == entt::null) return entt::null;

		entt::entity current = target;

		while (current != entt::null) {
			auto* h = registry.try_get<CHeirarchy>(current);
			if (!h) return entt::null;

			if (h->next == entt::null)
				return current;

			current = h->next;
		}

		return entt::null;
	}

	entt::entity CHeirarchyService::root(entt::entity target) {
		if (target == entt::null) return entt::null;

		entt::entity current = target;

		while (current != entt::null) {
			auto* h = registry.try_get<CHeirarchy>(current);
			if (!h) return current; // treat as its own root

			if (h->parent == entt::null)
				return current;

			current = h->parent;
		}

		return entt::null;
	}

	entt::entity CHeirarchyService::add_sister(entt::entity target) {
		if (target == entt::null) return entt::null;
		if (!registry.all_of<CHeirarchy>(target)) return entt::null;
		
		entt::entity child = registry.create();
		// mark it as dirty so systems know
		registry.emplace<CHeirarchy::DirtyFlag>(child);
		auto& t = registry.get<CHeirarchy>(target);
		if (registry.get<CHeirarchy>(target).child == entt::null) {
			registry.emplace<CHeirarchy>(child).parent = target;
			t.child = child;
			return child;
		}

		return add_sister(t.child);


	}



	

}