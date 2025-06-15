#include "GLFWCallback.h"

callback::GLFWCallback::GLFWCallback() {
    this->keyDispatcher = std::make_shared<callback::KeyDispatcher>();
}

void callback::GLFWCallback::connect(GLFWwindow* window) {
    glfwSetKeyCallback(window, glfwKeyEvent);
}

void callback::GLFWCallback::bind(GLFWwindow* window) {
    glfwSetWindowUserPointer(window, this);
}

void callback::GLFWCallback::glfwKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* cb = static_cast<GLFWCallback*>(glfwGetWindowUserPointer(window));

    if (cb != nullptr) {
	cb->keyDispatcher->onKeyEvent(KeyEvent(window, key, scancode, action, mods));
    }
}

std::shared_ptr<callback::KeyDispatcher> callback::GLFWCallback::getKeyEvent() const {
    return keyDispatcher;
}