#pragma once

#include <glad/glad.h>
#include <memory>

namespace tex {

class Texture {
public:
    Texture(const char* path);

    ~Texture();//delete texture from videocard space

    void bindSampler(int sampler);

    GLuint getTexture() const;

    int getWidth() const;

    int getHeight() const;

    int getCnt() const;

    void destroy();
private:
    GLuint texture;
    int width, height, cnt;

    GLuint createTexture(unsigned char* content, int width, int height, int cnt);

    unsigned char* loadTexture(const char* path, int &width, int &height, int &cnt);

    void deleteImageFromCPU(unsigned char* content);
};

}