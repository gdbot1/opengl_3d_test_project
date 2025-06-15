#include "KeyEvent.h"

callback::KeyEvent::KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
	: window(window), key(key), scancode(scancode), action(action), mods(mods) {}

GLFWwindow* callback::KeyEvent::getWindow() const {
    return window;
}

int callback::KeyEvent::getKey() const {
    return key;
}

int callback::KeyEvent::getScancode() const {
    return scancode;
}

int callback::KeyEvent::getAction() const {
    return action;
}

int callback::KeyEvent::getMods() const {
    return mods;
}