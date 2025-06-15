#include "Window.h"

#include <iostream>

gr::Window::Window(GLFWwindow* window) {
    this->window = window;
}

gr::Window::Window(int width, int height, const char* title) {
    glfwDefaultWindowHints();

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (window == nullptr) {
	std::cerr << "FATAL ERROR: window can't be created" << std::endl;

	this->window = nullptr;
    }
    else {
	glfwMakeContextCurrent(window);

	this->window = window;
    }
}
    
gr::Window::~Window() {
    glfwDestroyWindow(this->window);
}

void gr::Window::createCallback() {
    callback = std::make_shared<callback::GLFWCallback>();

    callback->bind(window);
    callback->connect(window);
}

GLFWwindow* gr::Window::getWindow() const {
    return this->window;
}

std::shared_ptr<callback::GLFWCallback> gr::Window::getCallback() const {
    return this->callback;
}