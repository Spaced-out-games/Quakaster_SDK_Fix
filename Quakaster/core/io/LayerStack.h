#pragma once
#include "../../core.h"
#include "ILayer.h"
#include "EventQueue.h"
#include <memory>
#include <vector>


namespace qk {
    class QK_API LayerStack {
        std::vector<std::unique_ptr<ILayer>> m_Layers;
        EventQueue* m_Queue = nullptr;

    public:

        void attach_queue(EventQueue* queue);

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

        ILayer* operator[](size_t index) {
            if (index >= m_Layers.size()) return nullptr;
            return m_Layers[index].get();
        }

        template<typename T, typename... Args>
        T& emplace_layer(Args&&... args)
        {
            static_assert(std::is_base_of_v<ILayer, T>);

            auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
            T& ref = *ptr;

            insert_layer(std::move(ptr));
            return ref;
        }

    };
}

