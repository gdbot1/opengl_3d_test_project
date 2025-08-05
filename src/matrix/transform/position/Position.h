#pragma once

#include "matrix/IMatrix.h"

namespace mtrx {

class Position {
public:
    Position(glm::vec3 position);

    virtual ~Position() = default;

    void translate(glm::vec3 motion);

    void setPosition(glm::vec3 position);

    glm::vec3 getPosition() const;
protected:
    glm::vec3 position;
};

}