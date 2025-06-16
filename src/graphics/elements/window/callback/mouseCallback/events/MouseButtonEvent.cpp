#include "MouseButtonEvent.h"

callback::MouseButtonEvent::MouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
	: window(window), button(button), action(action), mods(mods) {}

GLFWwindow* callback::MouseButtonEvent::getWindow() const {
    return window;
}

int callback::MouseButtonEvent::getButton() const {
    return button;
}

int callback::MouseButtonEvent::getAction() const {
    return action;
}

int callback::MouseButtonEvent::getMods() const {
    return mods;
}