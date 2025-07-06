#include "BindFBO.h"

render::BindFBO::BindFBO(std::shared_ptr<FBO> fbo, bool status) : fbo(fbo), status(status) {}

void render::BindFBO::render(RenderParam &param) {
    if (!fbo) {
	std::cerr << "BINDFBO ERROR: fbo is nullptr" << std::endl;
	return;
    }

    if (this->status) {
	fbo->bind();
    }
    else {
	fbo->unbind();
    }
}