#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"

#include "stb_image.h"

tex::Texture::Texture(const char* path) : texture() {
    unsigned char* content = loadTexture(path, this->width, this->height, this->cnt);

    this->texture = createTexture(content, width, height, cnt);

    deleteImageFromCPU(content);
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

GLuint tex::Texture::createTexture(unsigned char* content, int width, int height, int cnt) {
    GLuint texture;

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, content);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

unsigned char* tex::Texture::loadTexture(const char* path, int &width, int &height, int &cnt) {
    return stbi_load(path, &width, &height, &cnt, 0);
}

void tex::Texture::deleteImageFromCPU(unsigned char* content) {
    stbi_image_free(content);
}