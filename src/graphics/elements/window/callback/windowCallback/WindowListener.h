#pragma once

#include "events/FramebufferSizeEvent.h"

namespace callback {

class WindowListener {
public:
    WindowListener() = default;

    virtual ~WindowListener() = default;

    virtual void onFramebufferSizeEvent(callback::FramebufferSizeEvent &event) = 0;
};

}