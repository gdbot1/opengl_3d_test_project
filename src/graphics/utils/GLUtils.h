#pragma once

#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gl {
    void glfwInit();

    void glInit();

    void clear();

    void terminate();
}