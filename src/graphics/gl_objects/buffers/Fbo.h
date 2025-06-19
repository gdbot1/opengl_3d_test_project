#pragma once

#include <glad/glad.h>

#include "graphics/gl_objects/texture/Texture.h"

class FBO {
public:
    FBO(GLuint target);

    FBO();

    ~FBO();

    void linkTexture(tex::Texture &texture, GLuint attachment, GLuint level);

    void bind();

    void unbind();

    GLuint getFBO() const;

    GLuint getTarget() const;

    void destroy();
protected:
    GLuint fbo, target;

    GLuint createFBO();

    void linkTexture(GLuint target, GLuint attachment, GLuint textarget, GLuint texture, GLuint level);
};