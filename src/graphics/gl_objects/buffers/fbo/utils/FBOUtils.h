#pragma once

#include <glad/glad.h>

namespace FBOUtils {

void bind(GLuint fbo);

void bind(GLuint target, GLuint fbo);

void unbind();

void unbind(GLuint target);

}