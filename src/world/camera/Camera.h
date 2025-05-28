#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Camera {
public:
    Camera();

    Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    ~Camera();

    glm::mat4 getViewMatrix();

    glm::mat4 getProjectionMatrix();

    void setProjectionMatrix(glm::mat4 projection_matrix);

    void setPerspectiveProjectionMatrix(float fov, float aspect, float near, float far);

    void setOrthogonalProjectionMatrix(float left, float right, float bottom, float top, float near, float far);

    void setPosition(glm::vec3 position);

    void setRotation(glm::vec3 rotation);

    void setScale(glm::vec3 scale);

    glm::vec3 getPosition();

    glm::vec3 getRotation();

    glm::vec3 getScale();
private:
    glm::vec3 position, rotation, scale;//x - roll, y - yaw, z - pitch
    glm::mat4 projection_matrix;//матрица проекции
};