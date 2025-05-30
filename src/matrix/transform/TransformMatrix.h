#pragma once

#include <iostream>

#include "../IMatrix.h"

namespace mtrx {

class TransformMatrix : mtrx::IMatrix {
public:
    TransformMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);//mode = 1

    TransformMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float mode, bool inverse);

    ~TransformMatrix() = default;

    glm::mat4 getMatrix() const override;

    void setPosition(glm::vec3 position);

    void setRotation(glm::vec3 rotation);

    void setScale(glm::vec3 scale);

    void setMode(float mode);

    void setInverse(bool inverse);

    glm::vec3 getPosition() const;

    glm::vec3 getRotation() const;

    glm::vec3 getScale() const;

    float getMode() const;

    bool getInverse() const;
private:
    glm::vec3 position, rotation, scale;//x - pitch, y - yaw, z - roll
    float mode;//множитель при getMatrix
    bool inverse;
};

}