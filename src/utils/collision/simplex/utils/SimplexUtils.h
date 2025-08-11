#pragma once

#include <cmath>
#include <memory>
#include <utility>
#include <vector>
#include <unordered_map>

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

int getEdgeUniqueHashcode(int a, int b, int max_i);

void stillOne(int a, int b, int max_i, std::unordered_map<int, int> &table, std::vector<int> &keys);

void still(simplex::SimplexFace &face, int max_i, std::unordered_map<int, int> &table, std::vector<int> &keys);

int getI1(int hash, int max_i);

int getI2(int hash, int max_i);

std::shared_ptr<simplex::SimplexFace> createFace(simplex::Simplex &simplex, int i1, int i2, int i3);

}