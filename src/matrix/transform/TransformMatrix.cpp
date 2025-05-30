#include "TransformMatrix.h"

mtrx::TransformMatrix::TransformMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: position(position), rotation(rotation), scale(scale), mode(1), inverse(false) {}

mtrx::TransformMatrix::TransformMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float mode, bool inverse)
	: position(position), rotation(rotation), scale(scale), mode(mode), inverse(inverse) {}

glm::mat4 mtrx::TransformMatrix::getMatrix() const {
    glm::mat4 view_matrix(1.0f);
    
    if (inverse) {
	view_matrix = glm::rotate(view_matrix, glm::radians(this->rotation.x * mode), glm::vec3(1, 0, 0));
	view_matrix = glm::rotate(view_matrix, glm::radians(this->rotation.y * mode), glm::vec3(0, 1, 0));
	view_matrix = glm::rotate(view_matrix, glm::radians(this->rotation.z * mode), glm::vec3(0, 0, 1));
	view_matrix = glm::translate(view_matrix, this->position * mode);
	view_matrix = glm::scale(view_matrix, mode / this->scale);
    } else {
	view_matrix = glm::translate(view_matrix, this->position * mode);

	view_matrix = glm::rotate(view_matrix, glm::radians(this->rotation.x * mode), glm::vec3(1, 0, 0));
	view_matrix = glm::rotate(view_matrix, glm::radians(this->rotation.y * mode), glm::vec3(0, 1, 0));
	view_matrix = glm::rotate(view_matrix, glm::radians(this->rotation.z * mode), glm::vec3(0, 0, 1));
	view_matrix = glm::scale(view_matrix, mode / this->scale);
    }

    return view_matrix;
}

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

void mtrx::TransformMatrix::setInverse(bool inverse) {
    this->inverse = inverse;
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

bool mtrx::TransformMatrix::getInverse() const {
    return this->inverse;
}