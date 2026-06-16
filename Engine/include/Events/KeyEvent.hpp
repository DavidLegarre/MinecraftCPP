#pragma once

#include "Events/Event.hpp"

class KeyEvent : public Event {
   public:
    explicit KeyEvent(int keyCode) : m_KeyCode(keyCode) {}

    int GetKeyCode() const { return m_KeyCode; }

   private:
    int m_KeyCode;
};