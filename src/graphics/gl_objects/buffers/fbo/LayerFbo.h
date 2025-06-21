#pragma once

#include <stdexcept>
#include <memory>

#include "Fbo.h"

#include "graphics/gl_objects/texture/DepthTexture.h"

class LayerFBO : public FBO {
public:
    LayerFBO(int width, int height);

    void cloneData(LayerFBO &to);

    void bind() override;

    void unbind() override;
    
    std::shared_ptr<tex::Texture> getColorTexture() const;

    std::shared_ptr<tex::DepthTexture> getDepthTexture() const;

    int getWidth() const;

    int getHeight() const;
protected:
    using FBO::linkTexture;

    int width, height;
    int template_viewport[4];

    std::shared_ptr<tex::Texture> color_texture;
    std::shared_ptr<tex::DepthTexture> depth_texture;
};