#include "FramebufferSizeEvent.h"

callback::FramebufferSizeEvent::FramebufferSizeEvent(GLFWwindow* window, int width, int height)
	: window(window), width(width), height(height) {}

GLFWwindow* callback::FramebufferSizeEvent::getWindow() const {
    return window;
}

int callback::FramebufferSizeEvent::getWidth() const {
    return width;
}

int callback::FramebufferSizeEvent::getHeight() const {
    return height;
}