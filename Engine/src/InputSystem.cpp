#include "InputSystem.hpp"

#include "Events/KeyPressedEvent.hpp"
#include "Renderer/OpenGL.hpp"

InputSystem::InputSystem(EventManager& eventManager)
    : m_EventManager(eventManager) {}

void InputSystem::OnEvent(const Event& event) {
    if (event.GetEventType() != EventType::KeyPressed) {
        return;
    }

    const auto& keyEvent = static_cast<const KeyPressedEvent&>(event);

    if (keyEvent.GetKey() == GLFW_KEY_Q) {
        DispatchAction(InputAction::CloseWindow);
    }
}

void InputSystem::Subscribe(ActionCallback callback) {
    m_ActionListeners.push_back(callback);
}

void InputSystem::DispatchAction(InputAction action) {
    for (const auto& listener : m_ActionListeners) {
        listener(action);
    }
}
