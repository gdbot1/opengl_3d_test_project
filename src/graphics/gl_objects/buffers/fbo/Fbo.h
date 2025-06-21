#pragma once

#include <glad/glad.h>

#include "graphics/gl_objects/texture/Texture.h"

class FBO {
public:
    FBO(GLuint target);

    FBO();

    virtual ~FBO();

    virtual void linkTexture(tex::Texture &texture, GLuint attachment, GLuint level);

    virtual void bind();

    virtual void unbind();

    virtual GLuint getFBO() const;

    virtual GLuint getTarget() const;

    virtual void destroy();
protected:
    GLuint fbo, target;

    GLuint createFBO();

    virtual void linkTexture(GLuint target, GLuint attachment, GLuint textarget, GLuint texture, GLuint level);
};