#pragma once
#include "IEvent.h"
#include <vector>
#include "../core.h"


namespace qk {
    struct QK_API EventQueue {
    private:
        std::vector<IEvent> m_Data;

    public:
        EventQueue();

        // --- vector-like API ---

        void push_back(const IEvent& e);
        void push_back(IEvent&& e);

        template<typename... Args>
        IEvent& emplace_back(Args&&... args) {
            return m_Data.emplace_back(std::forward<Args>(args)...);
        }

        const std::vector<IEvent>& events();

        void clear();

        size_t size() const;
        bool empty() const;

        IEvent& operator[](size_t i) { return m_Data[i]; }
        const IEvent& operator[](size_t i) const { return m_Data[i]; }

        IEvent* data();
        const IEvent* data() const;

        // Iteration
        auto begin();
        auto end();
    };
}