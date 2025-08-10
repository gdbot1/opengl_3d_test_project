#pragma once

#include <glm/glm.hpp>

namespace simplex {

struct SimplexPoint {
    glm::vec3 point;

    SimplexPoint() = default;

    SimplexPoint(glm::vec3 point) : point(point) {}

    virtual ~SimplexPoint() = default;
};

}