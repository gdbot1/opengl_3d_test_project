#pragma once

#include "matrix/projection/ProjectionMatrix.h"

namespace mtrx {

class PerspectiveMatrix : public mtrx::ProjectionMatrix {
public:
    PerspectiveMatrix(float fov, float aspect, float near, float far);

    virtual ~PerspectiveMatrix() = default;
protected:
    float fov, aspect, near, far;

    glm::mat4 createMatrix(float fov, float aspect, float near, float far);
};

}