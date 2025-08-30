#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "IHitbox.h"

namespace gjk {

class OBBHitbox : public IHitbox {
public:
    OBBHitbox(const std::vector<glm::vec3> vertices);

    OBBHitbox(std::vector<glm::vec3>&& vertices);

    virtual ~OBBHitbox() = default;

    virtual glm::vec3 support(glm::vec3 direction) const override;

    virtual glm::vec3 getCenter() const override;
private:
    std::vector<glm::vec3> vertices;
};

}