#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace mtrx {

class IMatrix {
public:
    virtual ~IMatrix() = default;

    virtual glm::mat4 getMatrix() const = 0;
};

}