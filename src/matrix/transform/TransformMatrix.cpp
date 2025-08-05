#include "TransformMatrix.h"

mtrx::TransformMatrix::TransformMatrix(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
	: mtrx::Position(position), mtrx::Rotation(rotation), mtrx::Scale(scale), mode(1) {}

mtrx::TransformMatrix::TransformMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: mtrx::Position(position), mtrx::Rotation(glm::quat(glm::radians(rotation))), mtrx::Scale(scale), mode(1) {}

void mtrx::TransformMatrix::setMode(float mode) {
    this->mode = mode;
}

float mtrx::TransformMatrix::getMode() const {
    return this->mode;
}