#pragma once

#include <utility>
#include <memory>
#include <stdexcept>

#include <glm/glm.hpp>

#include "utils/math/MathUtils.h"

#include "utils/collision/gjk/hitbox/IHitbox.h"

#include "utils/collision/simplex/Simplex.h"
#include "utils/collision/simplex/utils/SimplexUtils.h"

namespace gjk {

std::shared_ptr<simplex::SimplexPoint> getMinkovskiDifferent(const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2, const glm::vec3 direction);

bool collision(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2, int &iterations);

bool collision(const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2);

int firstStage(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2, glm::vec3 &direction);

int secondStage(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2);

int thirdStage(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2);

int fourthStage(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2);

int finalStage(simplex::Simplex &simplex);

}