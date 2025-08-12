#pragma once

#include <glm/glm.hpp>

namespace simplex {

struct SimplexPoint {
    glm::vec3 point, support;

    SimplexPoint() = default;

    SimplexPoint(glm::vec3 point, glm::vec3 support) : point(point), support(support) {}

    virtual ~SimplexPoint() = default;
};

}