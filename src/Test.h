#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/component_wise.hpp> // теперь без ошибки

void printQuat(const glm::quat& q, const std::string& name) {
    std::cout << name << ": Q[w:" << q.w << ", x:" << q.x << ", y:" << q.y << ", z:" << q.z << "]\n";
}

void printEuler(const glm::vec3& euler, const std::string& name) {
    std::cout << name << ": x: " << glm::degrees(euler.x) 
              << " y: " << glm::degrees(euler.y) 
              << " z: " << glm::degrees(euler.z) << std::endl;
}

int foo() {
    // Исходная точка как кватернион (w=0, x=1, y=0, z=0)
    glm::quat pointQuat(0, 1, 0, 0);
    printQuat(pointQuat, "point");

    // Ось вращения (например, вектор (0, 1, 1)), нормализуем
    glm::vec3 axis(0, 1, 1);
    axis = glm::normalize(axis);

    // Поворачиваем на -90 градусов
    float angleDeg = -90.0f;
    float angleRad = glm::radians(angleDeg);
    glm::quat rotQuat = glm::angleAxis(angleRad, axis);
    printQuat(rotQuat, "axis (rotation quaternion)");

    // Получаем углы Эйлера из кватерниона поворота
    glm::vec3 eulerAngles = glm::eulerAngles(rotQuat);
    printEuler(eulerAngles, "euler angles");

    // Поворот точки: rotated_point = rotQuat * pointQuat * conjugate(rotQuat)
    glm::quat rotatedPoint = rotQuat * pointQuat * glm::conjugate(rotQuat);
    printQuat(rotatedPoint, "rotated");

    return 0;
}