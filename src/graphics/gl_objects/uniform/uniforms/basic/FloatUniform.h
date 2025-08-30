#pragma once

#include <string>

#include "graphics/gl_objects/uniform/Uniform.h"

class FloatUniform : public Uniform<float> {
public:
    FloatUniform(const std::string &path);

    FloatUniform(float value);

    virtual ~FloatUniform() = default;

    virtual void uniform() const override;
};