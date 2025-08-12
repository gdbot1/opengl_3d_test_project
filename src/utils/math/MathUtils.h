#pragma once

#include <cmath>

#include <glm/glm.hpp>

namespace math {

glm::vec3 vectorAB(glm::vec3 a, glm::vec3 b);

float distanceTo(glm::vec3 vector, glm::vec3 normal);

glm::vec3 spin(float yaw, float pitch, float radius);

}