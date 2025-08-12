#pragma once

#include <memory>
#include <cmath>
#include <vector>

#include <glm/glm.hpp>

#include "utils/math/MathUtils.h"

#include "graphics/gl_objects/Vao_e.h"
#include "graphics/gl_objects/buffers/Ebo.h"

#include "Object.h"

class Sphere : public Object {
public:
    Sphere(float x, float y, float z, float radius, int segments, int stacks);

    virtual ~Sphere() = default;

    glm::vec3 getPosition() const;

    float getRadius() const;

    glm::vec2 getDimension() const;
private:
    float x, y, z, radius;
    int segments, stacks;

    std::shared_ptr<VAO> createSphere(float x, float y, float z, float radius, int segments, int stacks);
};