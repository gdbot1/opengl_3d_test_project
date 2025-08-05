#include "Position.h"

mtrx::Position::Position(glm::vec3 position) : position(position) {}

void mtrx::Position::translate(glm::vec3 motion) {
    this->position += motion;
}

void mtrx::Position::setPosition(glm::vec3 position) {
    this->position = position;
}

glm::vec3 mtrx::Position::getPosition() const {
    return this->position;
}