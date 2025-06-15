#pragma once

#include <GLFW/glfw3.h>

#include <memory>

#include "keyCallback/KeyDispatcher.h"

namespace callback {

class GLFWCallback {
public:
    GLFWCallback();

    ~GLFWCallback() = default;

    void connect(GLFWwindow* window);

    void bind(GLFWwindow* window);
    
    static void glfwKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

    std::shared_ptr<callback::KeyDispatcher> getKeyEvent() const;
private:
    std::shared_ptr<callback::KeyDispatcher> keyDispatcher;
};

}