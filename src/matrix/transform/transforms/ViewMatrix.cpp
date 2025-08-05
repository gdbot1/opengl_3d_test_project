#include "ViewMatrix.h"

mtrx::ViewMatrix::ViewMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: mtrx::TransformMatrix(position, rotation, scale) {}

glm::mat4 mtrx::ViewMatrix::getMatrix() const {
    glm::mat4 view_matrix(1.0f);

    //view_matrix = glm::rotate(view_matrix, glm::radians(mtrx::TransformMatrix::rotation.x * mtrx::TransformMatrix::mode), glm::vec3(1, 0, 0));
    //view_matrix = glm::rotate(view_matrix, glm::radians(mtrx::TransformMatrix::rotation.y * mtrx::TransformMatrix::mode), glm::vec3(0, 1, 0));
    //view_matrix = glm::rotate(view_matrix, glm::radians(mtrx::TransformMatrix::rotation.z * mtrx::TransformMatrix::mode), glm::vec3(0, 0, 1));

    //view_matrix *= glm::inverse(glm::toMat4(mtrx::TransformMatrix::rotation));

    view_matrix *= glm::toMat4(glm::conjugate(rotation));

    view_matrix = glm::translate(view_matrix, position * mode);
    view_matrix = glm::scale(view_matrix, mode / compression);

    return view_matrix;
}