#include "MathUtils.h"

glm::vec3 math::vectorAB(glm::vec3 a, glm::vec3 b) {
    return glm::vec3(b.x - a.x, b.y - a.y, b.z - a.z);
}

float math::distanceTo(glm::vec3 vector, glm::vec3 normal) {
    return glm::dot(glm::normalize(normal), vector);
}

glm::vec3 math::spin(float yaw, float pitch, float radius) {
    float cosYaw = std::cos(yaw), cosPitch = std::cos(pitch);
    float sinYaw = std::sin(yaw), sinPitch = std::sin(pitch);

    return glm::vec3(
	sinPitch * cosYaw * radius,
	cosPitch * radius,
	sinPitch * sinYaw * radius
    );
}