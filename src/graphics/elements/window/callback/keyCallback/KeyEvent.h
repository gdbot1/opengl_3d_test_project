#pragma once

#include <GLFW/glfw3.h>

namespace callback {

class KeyEvent {
public:
    KeyEvent() = default;

    KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

    ~KeyEvent() = default;

    GLFWwindow* getWindow() const;

    int getKey() const;

    int getScancode() const;

    int getAction() const;

    int getMods() const;
protected:
    GLFWwindow* window;
    int key, scancode, action, mods;
};

}