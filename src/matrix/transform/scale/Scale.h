#pragma once

#include "matrix/IMatrix.h"

namespace mtrx {

class Scale {
public:
    Scale(glm::vec3 compression);

    virtual ~Scale() = default;

    void scale(glm::vec3 compression);

    void setScale(glm::vec3 compression);

    glm::vec3 getScale() const;
protected:
    glm::vec3 compression;
};

}