#pragma once

#include <GLFW/glfw3.h>

#include <memory>

#include "keyCallback/KeyDispatcher.h"
#include "mouseCallback/MouseDispatcher.h"
#include "windowCallback/WindowDispatcher.h"

namespace callback {

class GLFWCallback {
public:
    GLFWCallback();

    ~GLFWCallback() = default;

    void connect(GLFWwindow* window);

    void bind(GLFWwindow* window);
    
    static void glfwKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    static void glfwMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
    
    static void glfwFramebufferSizeEvent(GLFWwindow* window, int width, int height);

    std::shared_ptr<callback::KeyDispatcher> getKeyEvent() const;

    std::shared_ptr<callback::MouseDispatcher> getMouseEvent() const;

    std::shared_ptr<callback::WindowDispatcher> getWindowEvent() const;
private:
    std::shared_ptr<callback::KeyDispatcher> keyDispatcher;
    std::shared_ptr<callback::MouseDispatcher> mouseDispatcher;
    std::shared_ptr<callback::WindowDispatcher> windowDispatcher;
};

}