#pragma once
#include "core/io/Layer.h"
#include "core/io/Event.h"
#include <iostream>
#include <format>

namespace qk {
    struct DebugEventLayer : Layer {
        EBlock on_event(const Event& evt) override {
            std::cout << std::format("{}\n", to_string(evt));
            return EBlock::Pass;
        }

        void on_render() override {}
        void on_attach() override {}
        void on_detach() override {}

        DebugEventLayer() {
            using enum EEventCategory;
            subscribe(cat_all);
        }
    };
}
