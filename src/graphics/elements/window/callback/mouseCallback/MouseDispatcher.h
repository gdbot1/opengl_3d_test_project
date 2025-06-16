#pragma once

#include <GLFW/glfw3.h>

#include "events/Dispatcher.h"
#include "MouseListener.h"

namespace callback {

class MouseDispatcher : public Dispatcher<callback::MouseListener> {
public:
    MouseDispatcher();

    ~MouseDispatcher() = default;

    virtual void onMouseButtonEvent(MouseButtonEvent &event);
};

}