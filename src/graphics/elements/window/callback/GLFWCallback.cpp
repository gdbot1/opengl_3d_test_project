#include "GLFWCallback.h"

callback::GLFWCallback::GLFWCallback() {
    this->keyDispatcher = std::make_shared<callback::KeyDispatcher>();
    this->mouseDispatcher = std::make_shared<callback::MouseDispatcher>();
    this->windowDispatcher = std::make_shared<callback::WindowDispatcher>();
}

void callback::GLFWCallback::connect(GLFWwindow* window) {
    glfwSetKeyCallback(window, glfwKeyEvent);
    glfwSetMouseButtonCallback(window, glfwMouseButtonEvent);
    glfwSetFramebufferSizeCallback(window, glfwFramebufferSizeEvent);
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

void callback::GLFWCallback::glfwMouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {
    auto* cb = static_cast<GLFWCallback*>(glfwGetWindowUserPointer(window));

    if (cb != nullptr) {
	cb->mouseDispatcher->onMouseButtonEvent(MouseButtonEvent(window, button, action, mods));
    }
}

void callback::GLFWCallback::glfwFramebufferSizeEvent(GLFWwindow* window, int width, int height) {
    auto* cb = static_cast<GLFWCallback*>(glfwGetWindowUserPointer(window));

    if (cb != nullptr) {
	cb->windowDispatcher->onFramebufferSizeEvent(FramebufferSizeEvent(window, width, height));
    }
}

std::shared_ptr<callback::KeyDispatcher> callback::GLFWCallback::getKeyEvent() const {
    return keyDispatcher;
}

std::shared_ptr<callback::MouseDispatcher> callback::GLFWCallback::getMouseEvent() const {
    return mouseDispatcher;
}

std::shared_ptr<callback::WindowDispatcher> callback::GLFWCallback::getWindowEvent() const {
    return windowDispatcher;
}