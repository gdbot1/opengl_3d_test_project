#pragma once

#include <GLFW/glfw3.h>

namespace callback {

class FramebufferSizeEvent {
public:
    FramebufferSizeEvent() = default;

    FramebufferSizeEvent(GLFWwindow* window, int width, int height);

    ~FramebufferSizeEvent() = default;

    GLFWwindow* getWindow() const;

    int getWidth() const;

    int getHeight() const;
protected:
    GLFWwindow* window;
    int width, height;
};

}