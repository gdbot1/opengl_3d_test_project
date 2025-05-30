#pragma once

#include <iostream>
#include <memory>

#include "../../matrix/projection/ProjectionMatrix.h"
#include "../../matrix/projection/OrthogonalMatrix.h"
#include "../../matrix/projection/PerspectiveMatrix.h"
#include "../../matrix/transform/TransformMatrix.h"

class Camera {
public:
    Camera(std::shared_ptr<mtrx::TransformMatrix> view_matrix, std::shared_ptr<mtrx::ProjectionMatrix> project_matrix);

    Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::shared_ptr<mtrx::ProjectionMatrix> project_matrix);

    Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float fov, float aspect, float near, float far);

    ~Camera() = default;

    std::shared_ptr<mtrx::ProjectionMatrix> getProjection();

    void setProjection(std::shared_ptr<mtrx::ProjectionMatrix> project_matrix);

    std::shared_ptr<mtrx::TransformMatrix> getView();

    void setView(std::shared_ptr<mtrx::TransformMatrix> view_matrix);
private:
    std::shared_ptr<mtrx::TransformMatrix> view_matrix;
    std::shared_ptr<mtrx::ProjectionMatrix> project_matrix;
};