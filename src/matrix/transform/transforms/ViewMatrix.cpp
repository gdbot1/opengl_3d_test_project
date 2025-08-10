#include "ViewMatrix.h"

mtrx::ViewMatrix::ViewMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: mtrx::TransformMatrix(position, mtrx::ViewMatrix::eulerToQuatByYXZ(rotation), scale) {}

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

void mtrx::ViewMatrix::rotate(glm::vec3 rotation) {
    Rotation::rotate(mtrx::ViewMatrix::eulerToQuatByYXZ(rotation));
}

void mtrx::ViewMatrix::setRotation(glm::vec3 rotation) {
    Rotation::setRotation(mtrx::ViewMatrix::eulerToQuatByYXZ(rotation));
}

glm::quat mtrx::ViewMatrix::eulerToQuatByYXZ(glm::vec3 vector) {
    glm::vec3 x(1, 0, 0), y(0, 1, 0), z(0, 0, 1);

    glm::vec3 rotation = glm::radians(vector);

    glm::quat r_x = glm::angleAxis(rotation.x, x);
    glm::quat r_y = glm::angleAxis(rotation.y, y);
    glm::quat r_z = glm::angleAxis(rotation.z, z);

    return r_y * r_x * r_z;
}