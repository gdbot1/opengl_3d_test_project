#pragma once

#include <glad/glad.h>
#include <memory>

#include "utils/TextureUtils.h"

namespace tex {

class Texture {
public:
    Texture(const char* path);

    Texture(int width, int height);

    virtual ~Texture();//delete texture from videocard space

    virtual void bindSampler(int sampler);

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