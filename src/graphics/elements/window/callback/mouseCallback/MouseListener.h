#pragma once

#include "events/MouseButtonEvent.h"

namespace callback {

class MouseListener {
public:
    MouseListener() = default;

    virtual ~MouseListener() = default;

    virtual void onMouseButtonEvent(callback::MouseButtonEvent &event) = 0;
};

}