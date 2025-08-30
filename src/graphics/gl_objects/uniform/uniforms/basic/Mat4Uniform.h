#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/gl_objects/uniform/Uniform.h"

class Mat4Uniform : public Uniform<glm::mat4> {
public:
    Mat4Uniform(const std::string &path);

    virtual ~Mat4Uniform() = default;

    virtual void uniform() const override;
};