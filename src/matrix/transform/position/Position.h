#pragma once

#include "matrix/IMatrix.h"

namespace mtrx {

class Position {
public:
    Position(glm::vec3 position);

    virtual ~Position() = default;

    virtual void translate(glm::vec3 motion);

    virtual void setPosition(glm::vec3 position);

    virtual glm::vec3 getPosition() const;
protected:
    glm::vec3 position;
};

}