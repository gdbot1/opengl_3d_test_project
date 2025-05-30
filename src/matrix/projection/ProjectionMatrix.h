#pragma once

#include "../IMatrix.h"

namespace mtrx {

class ProjectionMatrix : public mtrx::IMatrix {
public:
    ProjectionMatrix(const glm::mat4 &mat);

    virtual ~ProjectionMatrix() = default;

    virtual void setMatrix(const glm::mat4 &mat);

    virtual glm::mat4 getMatrix() const override;
protected:
    glm::mat4 mat;

    ProjectionMatrix();
};

}