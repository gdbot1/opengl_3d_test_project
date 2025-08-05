#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/component_wise.hpp>

#include "matrix/IMatrix.h"
#include "matrix/transform/position/Position.h"
#include "matrix/transform/rotation/Rotation.h"
#include "matrix/transform/scale/Scale.h"

namespace mtrx {

class TransformMatrix : public mtrx::IMatrix, public mtrx::Position, public mtrx::Rotation, public mtrx::Scale {
public:
    TransformMatrix(glm::vec3 position, glm::quat rotation, glm::vec3 scale);//mode = 1

    TransformMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);//mode = 1

    virtual ~TransformMatrix() = default;

    virtual glm::mat4 getMatrix() const override = 0;

    void setMode(float mode);

    float getMode() const;
protected:
    float mode;//множитель при getMatrix
};

}