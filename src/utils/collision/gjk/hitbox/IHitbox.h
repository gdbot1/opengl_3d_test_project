#pragma once

#include <glm/glm.hpp>

#include "utils/collision/aabb/IHitbox.h"

namespace gjk {

class IHitbox : public aabb::IHitbox {
public:
    virtual glm::vec3 support(glm::vec3 direction) const = 0;

    virtual glm::vec3 getCenter() const = 0;

    virtual ~IHitbox() = default;
};

}