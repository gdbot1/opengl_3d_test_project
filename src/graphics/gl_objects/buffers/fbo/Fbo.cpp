#include "Fbo.h"

FBO::FBO(GLuint target) {
    this->fbo = createFBO();
    this->target = target;
}

FBO::FBO() {
    this->fbo = createFBO();
    this->target = GL_FRAMEBUFFER;
}

FBO::~FBO() {
    destroy();
}

void FBO::linkTexture(tex::Texture &texture, GLuint attachment, GLuint level) {
    linkTexture(target, attachment, texture.getTarget(), texture.getTexture(), level);
}

GLuint FBO::createFBO() {
    GLuint fbo;

    glGenFramebuffers(1, &fbo);

    return fbo;
}

void FBO::bind() {
    glBindFramebuffer(target, this->fbo);
}

void FBO::unbind() {
    glBindFramebuffer(target, 0);
}

GLuint FBO::getFBO() const {
    return this->fbo;
}

GLuint FBO::getTarget() const {
    return this->target;
}

void FBO::destroy() {
    glDeleteFramebuffers(1, &fbo);
}

void FBO::linkTexture(GLuint target, GLuint attachment, GLuint textarget, GLuint texture, GLuint level) {
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
}