#include "TransformMatrix.h"

mtrx::TransformMatrix::TransformMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: position(position), rotation(rotation), scale(scale), mode(1) {}

mtrx::TransformMatrix::TransformMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float mode)
	: position(position), rotation(rotation), scale(scale), mode(mode) {}

void mtrx::TransformMatrix::setPosition(glm::vec3 position) {
    this->position = position;
}

void mtrx::TransformMatrix::setRotation(glm::vec3 rotation) {
    this->rotation = rotation;
}

void mtrx::TransformMatrix::setScale(glm::vec3 scale) {
    this->scale = scale;
}

void mtrx::TransformMatrix::setMode(float mode) {
    this->mode = mode;
}

glm::vec3 mtrx::TransformMatrix::getPosition() const {
    return this->position;
}

glm::vec3 mtrx::TransformMatrix::getRotation() const {
    return this->rotation;
}

glm::vec3 mtrx::TransformMatrix::getScale() const {
    return this->scale;
}

float mtrx::TransformMatrix::getMode() const {
    return this->mode;
}