#pragma once

#include <glm/glm.hpp>

namespace gjk {

class IHitbox {
public:
    virtual glm::vec3 support(glm::vec3 direction) const = 0;

    virtual glm::vec3 getCenter() const = 0;

    virtual ~IHitbox() = default;
};

}