#pragma once

#include <GLFW/glfw3.h>

#include "events/Dispatcher.h"
#include "WindowListener.h"

namespace callback {

class WindowDispatcher : public Dispatcher<callback::WindowListener> {
public:
    WindowDispatcher();

    ~WindowDispatcher() = default;

    virtual void onFramebufferSizeEvent(FramebufferSizeEvent &event);
};

}