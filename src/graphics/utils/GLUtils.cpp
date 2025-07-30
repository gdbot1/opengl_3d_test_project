#include "GLUtils.h"

void gl::glfwInit() {
    if (!::glfwInit()) {
	throw std::runtime_error("GLUTILS ERROR: glfwInit() error: glfw is not initilized");
    }
}

void gl::glInit() {
    if (!gladLoadGL()) {
	gl::terminate();
	throw std::runtime_error("GLUTILS ERROR: glInit() error: gl is not initilized (gladLoadGL() error)");
    }
}

void gl::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gl::terminate() {
    glfwTerminate();
}