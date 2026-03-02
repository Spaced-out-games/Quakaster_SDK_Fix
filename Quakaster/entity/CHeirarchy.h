#pragma once

#include "entt/entity/entity.hpp"
#include "entt/entity/registry.hpp"
#include "../core.h"
#include "../core/IService.h"

namespace qk::entity {
	// Used to define an entity heirarchy
	struct QK_API CHeirarchy {
		entt::entity parent = entt::null;
		entt::entity child	= entt::null;
		entt::entity prev	= entt::null;
		entt::entity next	= entt::null;

		struct DirtyFlag {
			entt::entity old_parent = entt::null;
		};

	};

	


	/*
	 Provides services for modifying
	 entity heirarchies
	*/
	struct QK_API CHeirarchyService : IService {
		entt::registry& registry;

		CHeirarchyService(entt::registry& target);


		// might template these with flag types
		entt::entity find_lowest_dirty_ancestor(entt::entity target);
		entt::entity find_highest_dirty_ancestor(entt::entity target);

		entt::entity find_lowest_common_ancestor(entt::entity t1, entt::entity t2);


		entt::entity first(entt::entity target);
		entt::entity last(entt::entity target);
		entt::entity root(entt::entity target);
		bool is_descendant(entt::entity parent, entt::entity child);



		entt::entity add_sister(entt::entity target);
		entt::entity add_child(entt::entity target);
		void detach(entt::entity target);

	};


}