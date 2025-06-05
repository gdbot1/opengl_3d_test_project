#include "Camera.h"

Camera::Camera(std::shared_ptr<mtrx::TransformMatrix> view_matrix, std::shared_ptr<mtrx::ProjectionMatrix> project_matrix) {
    this->view_matrix = view_matrix;
    this->project_matrix = project_matrix;
}

Camera::Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::shared_ptr<mtrx::ProjectionMatrix> project_matrix) {
    this->view_matrix = std::make_shared<mtrx::ViewMatrix>(position, rotation, scale, 1);
    this->project_matrix = project_matrix;
}

Camera::Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    this->view_matrix = std::make_shared<mtrx::ViewMatrix>(position, rotation, scale, 1);
    this->project_matrix = std::make_shared<mtrx::OrthogonalMatrix>(-1, 1, -1, 1, -1, 1);
}

Camera::Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float fov, float aspect, float near, float far) {
    this->view_matrix = std::make_shared<mtrx::ViewMatrix>(position, rotation, scale, 1);
    this->project_matrix = std::make_shared<mtrx::PerspectiveMatrix>(fov, aspect, near, far);
}

std::shared_ptr<mtrx::ProjectionMatrix> Camera::getProjection() {
    return this->project_matrix;
}

void Camera::setProjection(std::shared_ptr<mtrx::ProjectionMatrix> project_matrix) {
    this->project_matrix = project_matrix;
}

std::shared_ptr<mtrx::TransformMatrix> Camera::getView() {
    return this->view_matrix;
}

void Camera::setView(std::shared_ptr<mtrx::TransformMatrix> view_matrix) {
    this->view_matrix = view_matrix;
}