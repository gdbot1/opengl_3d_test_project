#pragma once

#include <memory>

#include "graphics/IRenderable.h"
#include "graphics/gl_objects/texture/Texture.h"

namespace render {

class Display : public IRenderable {
public:
    Display(std::shared_ptr<tex::Texture> texture);

    void render(RenderParam &param) override;
private:
    std::shared_ptr<tex::Texture> texture;
};

}