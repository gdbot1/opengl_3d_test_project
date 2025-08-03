#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/component_wise.hpp>

#include "../IMatrix.h"

namespace mtrx {

class TransformMatrix : mtrx::IMatrix {
public:
    TransformMatrix(glm::vec3 position, glm::quat rotation, glm::vec3 scale);//mode = 1

    TransformMatrix(glm::vec3 position, glm::quat rotation, glm::vec3 scale, float mode);

    TransformMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);//mode = 1

    TransformMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float mode);

    virtual ~TransformMatrix() = default;

    virtual glm::mat4 getMatrix() const override = 0;

    void setPosition(glm::vec3 position);

    void setRotation(glm::vec3 rotation);

    void setRotation(glm::quat rotation);

    void setScale(glm::vec3 scale);

    void setMode(float mode);

    glm::vec3 getPosition() const;

    glm::vec3 getRotation() const;

    glm::vec3 getScale() const;

    float getMode() const;
protected:
    glm::vec3 position, scale;//x - pitch, y - yaw, z - roll
    glm::quat rotation;
    float mode;//множитель при getMatrix
};

}