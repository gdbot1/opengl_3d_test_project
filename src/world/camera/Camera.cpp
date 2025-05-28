#include "Camera.h"

using namespace std;

Camera::Camera() {}

Camera::Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: position(position), rotation(rotation), scale(scale) {}

Camera::~Camera() {}

glm::mat4 Camera::getViewMatrix() {
    glm::mat4 view_matrix(1.0f);
    
    view_matrix = glm::rotate(view_matrix, glm::radians(-this->rotation.z), glm::vec3(1, 0, 0));
    view_matrix = glm::rotate(view_matrix, glm::radians(-this->rotation.y), glm::vec3(0, 1, 0));
    view_matrix = glm::rotate(view_matrix, glm::radians(-this->rotation.x), glm::vec3(0, 0, 1));
    view_matrix = glm::translate(view_matrix, -this->position);
    view_matrix = glm::scale(view_matrix, 1.0f / this->scale);

    return view_matrix;
}

glm::mat4 Camera::getProjectionMatrix() {
    return this->projection_matrix;
}

void Camera::setProjectionMatrix(glm::mat4 projection_matrix) {
    this->projection_matrix = projection_matrix;
}

void Camera::setPerspectiveProjectionMatrix(float fov, float aspect, float near, float far) {
    this->projection_matrix = glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::setOrthogonalProjectionMatrix(float left, float right, float bottom, float top, float near, float far) {
    this->projection_matrix = glm::ortho(left, right, bottom, top, near, far);
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
}

void Camera::setRotation(glm::vec3 rotation) {
    this->rotation = rotation;
}

void Camera::setScale(glm::vec3 scale) {
    this->scale = scale;
}

glm::vec3 Camera::getPosition() {
    return this->position;
}

glm::vec3 Camera::getRotation() {
    return this->rotation;
}

glm::vec3 Camera::getScale() {
    return this->scale;
}