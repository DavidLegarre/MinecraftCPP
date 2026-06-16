#pragma once

#include <functional>
#include <vector>

#include "Events/Event.hpp"
#include "InputAction.hpp"

class EventManager;

class InputSystem {
    using ActionCallback = std::function<void(InputAction)>;

   public:
    explicit InputSystem(EventManager& eventManager);

    void OnEvent(const Event& event);
    void Subscribe(ActionCallback callback);

   private:
    std::vector<ActionCallback> m_ActionListeners;
    EventManager& m_EventManager;

    void DispatchAction(InputAction action);
};
