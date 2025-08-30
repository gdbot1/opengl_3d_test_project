#pragma once

#include <string>

#include <glm/glm.hpp>

#include "graphics/gl_objects/uniform/Uniform.h"

class Vec2Uniform : public Uniform<glm::vec2> {
public:
    Vec2Uniform(const std::string &path);

    virtual ~Vec2Uniform() = default;

    virtual void uniform() const override;
};