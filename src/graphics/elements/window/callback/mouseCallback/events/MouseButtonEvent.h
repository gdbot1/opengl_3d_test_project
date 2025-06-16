#pragma once

#include <GLFW/glfw3.h>

namespace callback {

class MouseButtonEvent {
public:
    MouseButtonEvent() = default;

    MouseButtonEvent(GLFWwindow* window, int button, int action, int mods);

    ~MouseButtonEvent() = default;

    GLFWwindow* getWindow() const;

    int getButton() const;

    int getAction() const;

    int getMods() const;
protected:
    GLFWwindow* window;
    int button, action, mods;
};

}