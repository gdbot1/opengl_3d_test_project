#pragma once

#include "../../shader/Program.h"

class RenderParam {
public:
    shared_ptr<Program> program;

    RenderParam(shared_ptr<Program> program);

    ~RenderParam() = default;
};