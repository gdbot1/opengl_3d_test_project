#include "OrthogonalMatrix.h"

mtrx::OrthogonalMatrix::OrthogonalMatrix(float left, float right, float bottom, float top, float near, float far) : mtrx::ProjectionMatrix(createMatrix(left, right, bottom, top, near, far)) {
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->near = near;
    this->far = far;
}

glm::mat4 mtrx::OrthogonalMatrix::createMatrix(float left, float right, float bottom, float top, float near, float far) {
    return glm::ortho(left, right, bottom, top, near, far);
}