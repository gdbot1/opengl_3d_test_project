#include "SphereHitbox.h"

gjk::SphereHitbox::SphereHitbox(float radius, std::shared_ptr<mtrx::TransformMatrix> model_matrix) : radius(radius), model_matrix(model_matrix) {}

glm::vec3 gjk::SphereHitbox::support(glm::vec3 direction) const {
    glm::mat4 mat = model_matrix->getMatrix();

    glm::vec3 correct_direction = glm::vec3(glm::inverse(mat) * glm::vec4(direction, 0.0f));

    glm::vec3 direction_n = glm::normalize(correct_direction);

    glm::vec3 sup = direction_n * radius;

    glm::vec3 e_sup = glm::vec3(mat * glm::vec4(sup, 1.0f));

    return e_sup;
}

glm::vec3 gjk::SphereHitbox::getCenter() const {
    return glm::vec3(model_matrix->getMatrix() * glm::vec4(0, 0, 0, 1.0f));
}

aabb::AABB gjk::SphereHitbox::getAABB() const {
    return aabb::AABB(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
}