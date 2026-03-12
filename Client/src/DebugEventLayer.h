#pragma once
#include "core/io/ILayer.h"
#include "core/io/Event.h"
#include <iostream>

namespace qk {
	struct DebugEventLayer : ILayer {
		EBlock on_event(const Event& evt) override {
			std::cout << qk::to_string(evt) << '\n';
			return EBlock::Pass;
		}

		virtual void on_render() override {

		}

		DebugEventLayer() {
			using enum EEventCategory;
			subscribe(cat_all);
		}

	};
}
