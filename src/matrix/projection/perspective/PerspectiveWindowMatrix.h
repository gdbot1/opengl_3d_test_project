#pragma once

#include "PerspectiveMatrix.h"
#include "graphics/elements/window/callback/windowCallback/WindowListener.h"
#include "graphics/elements/window/callback/windowCallback/events/FramebufferSizeEvent.h"

namespace mtrx {

class PerspectiveWindowMatrix : public mtrx::PerspectiveMatrix, public callback::WindowListener {
public:
    PerspectiveWindowMatrix(float fov, float aspect, float near, float far);

    void onFramebufferSizeEvent(callback::FramebufferSizeEvent &event) override;
protected:
    
};

}