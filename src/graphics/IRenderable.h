#pragma once

#include "graphics/param/RenderParam.h"

class IRenderable {
public:
    virtual ~IRenderable() = default;

    virtual void render(RenderParam &param) = 0;
};