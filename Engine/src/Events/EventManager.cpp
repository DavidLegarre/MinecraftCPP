#include "Events/EventManager.hpp"

void EventManager::Subscribe(EventCallback callback) {
    m_Listeners.push_back(callback);
}

void EventManager::Dispatch(const Event& event) {
    for (const auto& listener : m_Listeners) {
        listener(event);
    }
}