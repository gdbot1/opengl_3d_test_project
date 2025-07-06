#include "FBOUtils.h"

void FBOUtils::bind(GLuint fbo) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FBOUtils::bind(GLuint target, GLuint fbo) {
    glBindFramebuffer(target, fbo);
}

void FBOUtils::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBOUtils::unbind(GLuint target) {
    glBindFramebuffer(target, 0);
}