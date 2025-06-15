#pragma once

#include <GLFW/glfw3.h>

#include "events/Dispatcher.h"
#include "KeyListener.h"

namespace callback {

class KeyDispatcher : public Dispatcher<callback::KeyListener> {
public:
    KeyDispatcher();

    ~KeyDispatcher() = default;

    virtual void onKeyEvent(KeyEvent &event);
};

}