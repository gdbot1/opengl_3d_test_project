#include "RenderParam.h"

RenderParam::RenderParam() {

}

RenderParam::RenderParam(shared_ptr<Program> program) {
    this->program = program;
}

RenderParam& RenderParam::setFBOInput(shared_ptr<LayerFBO> fbo_input) {
    this->fbo_input = fbo_input;

    return *this;
}

RenderParam& RenderParam::setFBOOutput(shared_ptr<LayerFBO> fbo_output) {
    this->fbo_output = fbo_output;

    return *this;
}

RenderParam& RenderParam::setAspect(float aspect) {
    this->aspect = aspect;

    return *this;
}

RenderParam& RenderParam::setProgram(shared_ptr<Program> program) {
    this->program = program;

    return *this;
}