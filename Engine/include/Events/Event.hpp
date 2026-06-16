#pragma once

enum class EventType {
    None,
    KeyPressed,
    KeyReleased,
};

class Event {
   public:
    virtual ~Event() = default;

    virtual EventType GetEventType() const = 0;
};