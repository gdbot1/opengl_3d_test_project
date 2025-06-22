#pragma once

#include "shader/Program.h"
#include "graphics/gl_objects/buffers/fbo/LayerFBO.h"

class RenderParam {
public:
    shared_ptr<Program> program;
    shared_ptr<LayerFBO> fbo_input, fbo_output;
    float aspect;

    RenderParam();

    RenderParam(shared_ptr<Program> program);

    ~RenderParam() = default;

    RenderParam& setFBOInput(shared_ptr<LayerFBO> fbo_input);

    RenderParam& setFBOOutput(shared_ptr<LayerFBO> fbo_output);

    RenderParam& setAspect(float aspect);

    RenderParam& setProgram(shared_ptr<Program> program);
};