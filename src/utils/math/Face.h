#pragma once

#include <glm/glm.hpp>

namespace math {

struct Face {
    glm::vec3 p1, p2, p3;

    Face(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3) : p1(p1), p2(p2), p3(p3) {}

    Face(const glm::vec3 &p) : p1(p), p2(p), p3(p) {}

    Face() : p1(glm::vec3(0, 0, 0)), p2(glm::vec3(0, 0, 0)), p3(glm::vec3(0, 0, 0)) {}

    virtual ~Face() = default;

    void setFace(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
    }
};

}