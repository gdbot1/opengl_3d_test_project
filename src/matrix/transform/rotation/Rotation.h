#pragma once

#include "matrix/IMatrix.h"

namespace mtrx {

class Rotation {
public:
    Rotation(glm::quat rotation);

    Rotation(glm::vec3 rotation);

    virtual ~Rotation() = default;

    void rotate(glm::quat rotation);

    void rotate(glm::vec3 rotation);

    void setRotation(glm::quat rotation);

    void setRotation(glm::vec3 rotation);

    glm::quat getRotationQuat() const;

    glm::vec3 getRotation() const;
protected:
    glm::quat rotation;
};

}