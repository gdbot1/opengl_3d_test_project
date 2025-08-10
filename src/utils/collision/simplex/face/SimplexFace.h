#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace simplex {

struct SimplexFace {
    int i1, i2, i3;
    float dist;
    glm::vec3 normal;

    SimplexFace(int i1, int i2, int i3, glm::vec3 normal, float dist) : i1(i1), i2(i2), i3(i3), normal(normal), dist(dist) {}

    virtual ~SimplexFace() = default;

    std::vector<int> getVertices() {
	return {i1, i2, i3};
    }
};

}