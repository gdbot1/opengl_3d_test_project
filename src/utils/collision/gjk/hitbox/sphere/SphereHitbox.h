#pragma once

#include <vector>
#include <limits>
#include <memory>

#include <glm/glm.hpp>

#include "utils/collision/gjk/hitbox/IHitbox.h"

#include "matrix/utils/MatrixUtils.h"

#include "matrix/transform/TransformMatrix.h"
#include "matrix/transform/transforms/ModelMatrix.h"

namespace gjk {

class SphereHitbox : public IHitbox {
public:
    SphereHitbox(float radius, std::shared_ptr<mtrx::TransformMatrix> model_matrix);

    virtual ~SphereHitbox() = default;

    virtual glm::vec3 support(glm::vec3 direction) const override;

    virtual glm::vec3 getCenter() const override;

    virtual aabb::AABB getAABB() const override;
private:
    float radius;
    std::shared_ptr<mtrx::TransformMatrix> model_matrix;
};

}