#pragma once

#include <glad/glad.h>
#include <memory>
#include <stdexcept>

#include "graphics/gl_objects/texture/utils/TextureUtils.h"

#include "utils/IBindable.h"

namespace tex {

class Texture : public IBindable {
public:
    Texture(const char* path);

    Texture(int width, int height);

    virtual ~Texture();//delete texture from videocard space

    virtual void bindSampler(int sampler);

    virtual void bind() override;

    virtual void unbind() override;

    virtual void clone(tex::Texture &to);

    virtual GLuint getTexture() const;

    virtual GLuint getTarget() const;

    virtual int getWidth() const;

    virtual int getHeight() const;

    virtual int getCnt() const;

    virtual void destroy();
protected:
    GLuint texture, target;
    int width, height, cnt;

    Texture() = default;
};

}