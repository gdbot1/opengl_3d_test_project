#include "Rotation.h"

mtrx::Rotation::Rotation(glm::quat rotation) : rotation(rotation) {}

mtrx::Rotation::Rotation(glm::vec3 rotation) : rotation(glm::quat(glm::normalize(rotation))) {}

void mtrx::Rotation::rotate(glm::quat rotation) {
    this->rotation = rotation * this->rotation;
}

void mtrx::Rotation::rotate(glm::vec3 rotation) {
    mtrx::Rotation::rotate(glm::quat(glm::radians(rotation)));
}

void mtrx::Rotation::setRotation(glm::vec3 rotation) {
    this->rotation = glm::quat(glm::radians(rotation));
}

void mtrx::Rotation::setRotation(glm::quat rotation) {
    this->rotation = rotation;
}

glm::quat mtrx::Rotation::getRotationQuat() const {
    return this->rotation;
}

glm::vec3 mtrx::Rotation::getRotation() const {
    return glm::degrees(glm::eulerAngles(glm::normalize(this->rotation)));
}