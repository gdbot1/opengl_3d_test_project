#include "ProjectionMatrix.h"

mtrx::ProjectionMatrix::ProjectionMatrix(const glm::mat4 &mat) : mat(mat) {}

mtrx::ProjectionMatrix::ProjectionMatrix() {

}

void mtrx::ProjectionMatrix::setMatrix(const glm::mat4 &mat) {
    this->mat = mat;
}

glm::mat4 mtrx::ProjectionMatrix::getMatrix() const {
    return this->mat;
}