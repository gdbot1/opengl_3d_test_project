#pragma once

#include <string>

#include <glm/glm.hpp>

#include "graphics/gl_objects/uniform/Uniform.h"

class Vec3Uniform : public Uniform<glm::vec3> {
public:
    Vec3Uniform(const std::string &path);

    Vec3Uniform(glm::vec3 value);

    virtual ~Vec3Uniform() = default;

    virtual void uniform() const override;
};