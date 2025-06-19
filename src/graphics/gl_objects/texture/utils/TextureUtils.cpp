#define STB_IMAGE_IMPLEMENTATION

#include "TextureUtils.h"

#include "stb_image.h"

void tex::uniformInteger(int program, const char* name, int value) {
    int un_loc = glGetUniformLocation(program, name);

    glUniform1i(un_loc, value);
}

GLuint tex::createRGBATexture(unsigned char* content, int width, int height, int cnt) {
    GLuint texture;

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, content);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

GLuint tex::createNullDepthTexture(int width, int height) {
    GLuint texture;

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

GLuint tex::createNullRGBATexture(int width, int height) {
    GLuint texture;

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

unsigned char* tex::loadTexture(const char* path, int &width, int &height, int &cnt) {
    return stbi_load(path, &width, &height, &cnt, 0);
}

void tex::deleteImageFromCPU(unsigned char* content) {
    stbi_image_free(content);
}