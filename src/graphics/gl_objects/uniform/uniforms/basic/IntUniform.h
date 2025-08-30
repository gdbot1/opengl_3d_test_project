#pragma once

#include <string>

#include "graphics/gl_objects/uniform/Uniform.h"

class IntUniform : public Uniform<int> {
public:
    IntUniform(const std::string &path);

    virtual ~IntUniform() = default;

    virtual void uniform() const override;
};