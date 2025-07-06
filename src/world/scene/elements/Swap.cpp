#include "Swap.h"

void render::Swap::render(RenderParam &param) {
    param.fbo_input->cloneData(*param.fbo_output);//clone fbo_input on fbo_output
}