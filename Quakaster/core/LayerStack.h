#pragma once
#include "../core.h"
#include "ILayer.h"
#include "EventQueue.h"
#include <memory>
#include <vector>


namespace qk {
    class QK_API LayerStack {
        std::vector<std::unique_ptr<ILayer>> m_Layers;
        std::shared_ptr<EventQueue> m_Queue = nullptr;

    public:

        void attach_queue(std::shared_ptr<EventQueue> queue);

        void insert_layer(std::unique_ptr<ILayer>&& layer);

        // Delete copy operations
        LayerStack(const LayerStack&) = delete;
        LayerStack& operator=(const LayerStack&) = delete;

        // Default move operations
        LayerStack(LayerStack&&) noexcept = default;
        LayerStack& operator=(LayerStack&&) noexcept = default;
        LayerStack() = default;

        void propagate_events();

        void render();
    };
}

