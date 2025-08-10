#include "MathUtils.h"

glm::vec3 math::vectorAB(glm::vec3 a, glm::vec3 b) {
    return glm::vec3(b.x - a.x, b.y - a.y, b.z - a.z);
}

float math::distanceTo(glm::vec3 vector, glm::vec3 normal) {
    return glm::dot(glm::normalize(normal), vector);
}