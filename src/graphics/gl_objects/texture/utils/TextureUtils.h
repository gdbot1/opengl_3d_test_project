#pragma once

#include <glad/glad.h>
#include "../Texture.h"

namespace tex {

void uniformInteger(int program, const char* name,  int value);

GLuint createRGBATexture(unsigned char* content, int width, int height, int cnt);

GLuint createNullRGBATexture(int width, int height);

GLuint createNullDepthTexture(int width, int height);

unsigned char* loadTexture(const char* path, int &width, int &height, int &cnt);

void deleteImageFromCPU(unsigned char* content);

}