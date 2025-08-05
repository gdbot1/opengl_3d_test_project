#include "Scale.h"

mtrx::Scale::Scale(glm::vec3 compression) : compression(compression) {}

void mtrx::Scale::scale(glm::vec3 compression) {
    this->compression *= compression;
}

void mtrx::Scale::setScale(glm::vec3 compression) {
    this->compression = compression;
}

glm::vec3 mtrx::Scale::getScale() const {
    return this->compression;
}