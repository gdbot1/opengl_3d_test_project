#pragma once

#include "matrix/IMatrix.h"

namespace mtrx {

class Rotation {
public:
    Rotation(glm::quat rotation);

    Rotation(glm::vec3 rotation);

    virtual ~Rotation() = default;

    virtual void rotate(glm::quat rotation);

    virtual void rotate(glm::vec3 rotation);

    virtual void setRotation(glm::quat rotation);

    virtual void setRotation(glm::vec3 rotation);

    virtual glm::quat getRotationQuat() const;

    virtual glm::vec3 getRotation() const;
protected:
    glm::quat rotation;
};

}