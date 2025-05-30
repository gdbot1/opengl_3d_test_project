#pragma once

#include "ProjectionMatrix.h"

namespace mtrx {

class PerspectiveMatrix : public mtrx::ProjectionMatrix {
public:
    PerspectiveMatrix(float fov, float aspect, float near, float far);

    ~PerspectiveMatrix() = default;
private:
    float fov, aspect, near, far;

    glm::mat4 createMatrix(float fov, float aspect, float near, float far);
};

}