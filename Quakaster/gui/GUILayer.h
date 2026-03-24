#pragma once
#include "../core/core/Window.h"
#include "../core/io/Layer.h"
#include "../core/io/DefaultEvents.h"
#include "../gui/Widget.h"
#include "../gui/gui.h"
#include "../core.h"
#include <vector>
#include <memory>

namespace qk::gui {

	struct QK_API GUILayer : io::Layer {
		std::vector<io::Layer*> m_Widgets;
		core::Window* m_Window = nullptr;

        EBlock on_event(const Event& evt) override;

        void on_render() override;

        void on_attach() override;

        void on_detach() override;

        GUILayer(core::Window* pWindow);

	};
}