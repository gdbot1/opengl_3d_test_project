#pragma once

#include <memory>
#include <iostream>

#include "graphics/IRenderable.h"
#include "graphics/gl_objects/buffers/fbo/FBO.h"
#include "graphics/gl_objects/buffers/fbo/utils/FBOUtils.h"

namespace render {

class BindFBO : public IRenderable {
public:
    BindFBO(std::shared_ptr<FBO> fbo, bool status);

    void render(RenderParam &param) override;
private:
    std::shared_ptr<FBO> fbo;
    bool status;
};

}