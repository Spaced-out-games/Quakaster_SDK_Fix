#pragma once

#include "entt/entity/entity.hpp"
#include "entt/entity/registry.hpp"
#include "entt/entity/view.hpp"
#include "../core.h"
#include "../core/utility/Service.h"
//#include "spdlog/spdlog.h"

namespace qk::ent {
	// Used to define an entity heirarchy
	struct QK_API CGraphNode {
		entt::entity parent = entt::null;
		entt::entity prev	= entt::null;
		entt::entity next	= entt::null;
		entt::entity first = entt::null;
		entt::entity last = entt::null;

		struct DirtyFlag {
			entt::entity old_parent = entt::null;
		};

	};

	




}

