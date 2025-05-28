#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.h"

class Cube : public Object{
public:
    Cube(float x, float y, float z, float width, float height, float depth);

    ~Cube();

    glm::vec3 getPosition();

    glm::vec3 getSize();
private:
    float x, y, z, width, height, depth;

    shared_ptr<VAO> createCube(float x, float y, float z, float width, float height, float depth);
};