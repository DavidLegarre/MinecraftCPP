#pragma once

#include <functional>
#include <vector>

#include "Events/Event.hpp"

class EventManager {
   public:
    using EventCallback = std::function<void(const Event&)>;

    void Subscribe(EventCallback callback);

    void Dispatch(const Event& event);

   private:
    std::vector<EventCallback> m_Listeners;
};