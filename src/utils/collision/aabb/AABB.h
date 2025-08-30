#pragma once

#include <glm/glm.hpp>

namespace aabb {

struct AABB {
    glm::vec3 position, size;

    AABB(const glm::vec3 &position, const glm::vec3 &size) : position(position), size(size) {}

    glm::vec3 getPosition() const {
	return position;
    }

    glm::vec3 getSize() const {
	return size;
    }
};

}