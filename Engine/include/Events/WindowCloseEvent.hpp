#pragma once

#include "Event.hpp"

class WindowCloseEvent : public Event {
   public:
    WindowCloseEvent() = default;

    EventType GetEventType() const override { return EventType::WindowClose; }
};
