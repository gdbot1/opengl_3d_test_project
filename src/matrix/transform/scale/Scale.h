#pragma once

#include "matrix/IMatrix.h"

namespace mtrx {

class Scale {
public:
    Scale(glm::vec3 compression);

    virtual ~Scale() = default;

    virtual void scale(glm::vec3 compression);

    virtual void setScale(glm::vec3 compression);

    virtual glm::vec3 getScale() const;
protected:
    glm::vec3 compression;
};

}