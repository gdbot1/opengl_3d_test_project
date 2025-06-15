#pragma once

#include <memory>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "callback/GLFWCallback.h"

namespace gr {

class Window {
public:
    Window(GLFWwindow* window);

    Window(int width, int height, const char* title);
    
    ~Window();

    void createCallback();

    GLFWwindow* getWindow() const;

    std::shared_ptr<callback::GLFWCallback> getCallback() const;
private:
    GLFWwindow* window;
    std::shared_ptr<callback::GLFWCallback> callback;
};

}