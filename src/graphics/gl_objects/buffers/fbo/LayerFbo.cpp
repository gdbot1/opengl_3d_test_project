#include "LayerFbo.h"

#include <iostream>

LayerFBO::LayerFBO(int width, int height) {
    this->fbo = createFBO();
    this->target = GL_FRAMEBUFFER;

    this->color_texture = std::make_shared<tex::Texture>(width, height);
    this->depth_texture = std::make_shared<tex::DepthTexture>(width, height);

    std::cout << "col " << color_texture->getWidth() << " " << color_texture->getHeight() << std::endl;

    this->width = width;
    this->height = height;

    bind();
    
    linkTexture(*color_texture, GL_COLOR_ATTACHMENT0, 0);
    linkTexture(*depth_texture, GL_DEPTH_ATTACHMENT, 0);

    unbind();
}

void LayerFBO::cloneData(LayerFBO &to) {
    if (!this->color_texture || !this->depth_texture) {
	throw std::runtime_error("LAYERFBO ERROR: clone fbo error, because 'this' fbo textures is nullptr");
    }
    if (!to.getColorTexture() || !to.getDepthTexture()) {
	throw std::runtime_error("LAYERFBO ERROR: clone fbo error, because 'to' fbo textures is nullptr");
    }

    this->color_texture->clone(*to.getColorTexture());
    this->depth_texture->clone(*to.getDepthTexture());
}

void LayerFBO::bind() {
    glGetIntegerv(GL_VIEWPORT, template_viewport);

    glBindFramebuffer(target, this->fbo);

    glViewport(0, 0, this->width, this->height);
}

void LayerFBO::unbind() {
    glBindFramebuffer(target, 0);

    glViewport(template_viewport[0], template_viewport[1], template_viewport[2], template_viewport[3]);
}

std::shared_ptr<tex::Texture> LayerFBO::getColorTexture() const {
    return this->color_texture;
}

std::shared_ptr<tex::DepthTexture> LayerFBO::getDepthTexture() const {
    return this->depth_texture;
}

int LayerFBO::getWidth() const {
    return this->width;
}

int LayerFBO::getHeight() const {
    return this->height;
}