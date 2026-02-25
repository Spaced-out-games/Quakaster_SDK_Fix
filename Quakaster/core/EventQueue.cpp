#include "EventQueue.h"


namespace qk {
    EventQueue::EventQueue() {
        m_Data.reserve(256);
    }

    void EventQueue::push_back(const IEvent& e) {
        m_Data.push_back(e);
    }

    void EventQueue::push_back(IEvent&& e) {
        m_Data.push_back(std::move(e));
    }



    void EventQueue::clear() {
        m_Data.clear();
    }

    size_t EventQueue::size() const {
        return m_Data.size();
    }
    bool EventQueue::empty() const {
        return m_Data.empty();
    }


    IEvent* EventQueue::data() { return m_Data.data(); }
    const IEvent* EventQueue::data() const { return m_Data.data(); }

    auto EventQueue::begin() { return m_Data.begin(); }
    auto EventQueue::end() { return m_Data.end(); }

}