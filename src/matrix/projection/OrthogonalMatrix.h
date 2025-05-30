#pragma once

#include "ProjectionMatrix.h"

namespace mtrx {

class OrthogonalMatrix : public mtrx::ProjectionMatrix {
public:
    OrthogonalMatrix(float left, float right, float bottom, float top, float near, float far);

    ~OrthogonalMatrix() = default;
private:
    float left, right, bottom, top, near, far;

    glm::mat4 createMatrix(float left, float right, float bottom, float top, float near, float far);
};

}