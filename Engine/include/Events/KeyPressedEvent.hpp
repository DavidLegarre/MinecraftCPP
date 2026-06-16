#pragma once

#include "KeyEvent.hpp"

class KeyPressedEvent : public KeyEvent {
   public:
    using KeyEvent::KeyEvent;

    EventType GetEventType() const override { return EventType::KeyPressed; }
};