#include "DepthTexture.h"

tex::DepthTexture::DepthTexture(int width, int height) {
    this->texture = tex::createNullDepthTexture(width, height);
    this->width = width;
    this->height = height;
    this->cnt = 1;
    this->target = GL_TEXTURE_2D;
}