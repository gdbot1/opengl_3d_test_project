#include "PerspectiveMatrix.h"

mtrx::PerspectiveMatrix::PerspectiveMatrix(float fov, float aspect, float near, float far) : mtrx::ProjectionMatrix(createMatrix(fov, aspect, near, far)) {
    this->fov = fov;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
}

glm::mat4 mtrx::PerspectiveMatrix::createMatrix(float fov, float aspect, float near, float far) {
    return glm::perspective(glm::radians(fov), aspect, near, far);
}