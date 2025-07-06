#pragma once

#include "graphics/IRenderable.h"

namespace render {

class Swap : public IRenderable {
public:
    void render(RenderParam &param) override;
};

}