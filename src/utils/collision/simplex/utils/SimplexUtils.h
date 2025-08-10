#pragma once

#include <cmath>
#include <memory>
#include <utility>
#include <vector>

#include "utils/collision/simplex/Simplex.h"

#include "utils/collision/simplex/face/SimplexFace.h"
#include "utils/collision/simplex/point/SimplexPoint.h"

#include "utils/math/MathUtils.h"

namespace simplex {

bool faceIsLookingAt(simplex::Simplex &simplex, simplex::SimplexFace &face, const glm::vec3 at);

bool faceIsLookingAtOrigin(simplex::Simplex &simplex, simplex::SimplexFace &face);

std::shared_ptr<glm::vec3> findNormal(simplex::Simplex &simplex, const int i1, const int i2, const int i3);

std::shared_ptr<float> faceDistanceToOrigin(simplex::Simplex &simplex, simplex::SimplexFace &face);

std::pair<int, int> getSameEdge(simplex::SimplexFace &face1, simplex::SimplexFace &face2);

}