#pragma once
#include "../gui/Widget.h"
#include "../core/utility/Service.h"
#include "../core/utility/ScopeTimer.h"
#include "../core.h"
#include <vector>
#include <memory>

namespace qk::services {

	struct QK_API GUIService : IService {
		std::vector<std::unique_ptr<gui::Widget>> m_Widgets;

		void draw();


	};

}