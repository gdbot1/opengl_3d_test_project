#pragma once

#include <glad/glad.h>

class IUniform {
public:
    virtual ~IUniform() = default;

    virtual void updateLoc(GLint program) = 0;

    virtual void uniform() const = 0;
};