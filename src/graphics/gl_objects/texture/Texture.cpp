#include "Texture.h"

tex::Texture::Texture(const char* path) : texture() {
    unsigned char* content = tex::loadTexture(path, this->width, this->height, this->cnt);

    this->texture = tex::createRGBATexture(content, width, height, cnt);
    this->target = GL_TEXTURE_2D;

    tex::deleteImageFromCPU(content);
}

tex::Texture::Texture(int width, int height) {
    this->texture = tex::createNullRGBATexture(width, height);
    this->width = width;
    this->height = height;
    this->cnt = 4;
    this->target = GL_TEXTURE_2D;
}

tex::Texture::~Texture() {
    destroy();
}

void tex::Texture::bindSampler(int sampler) {
    glActiveTexture(GL_TEXTURE0 + sampler);

    glBindTexture(GL_TEXTURE_2D, texture);
}

GLuint tex::Texture::getTexture() const {
    return this->texture;
}

GLuint tex::Texture::getTarget() const {
    return this->target;
}

int tex::Texture::getWidth() const {
    return this->width;
}

int tex::Texture::getHeight() const {
    return this->height;
}

int tex::Texture::getCnt() const {
    return this->cnt;
}

void tex::Texture::destroy() {
    glDeleteTextures(1, &this->texture);
}