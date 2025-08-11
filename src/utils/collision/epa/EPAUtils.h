#pragma once

#include "utils/collision/epa/result/CollisionResult.h"

#include "utils/collision/gjk/GJKUtils.h"
#include "utils/collision/gjk/hitbox/IHitbox.h"

namespace epa {

void collision(const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2, epa::CollisionResult &result, int &iterations);

bool grow(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2, std::vector<int> &sort, epa::CollisionResult &result);

std::shared_ptr<std::vector<std::shared_ptr<simplex::SimplexFace>>> smashSimplex(simplex::Simplex &simplex, int i_new, std::vector<int> &faces_that_looking_at_new_point);

void getFacesThatLookingAt(simplex::Simplex &simplex, const glm::vec3 &point, std::vector<int> &faces_id);

void storeEdges(const simplex::Simplex &simplex, const std::vector<int> &faces_id, int max, std::unordered_map<int, int> &table, std::vector<int> &keys);

void deleteFaces(simplex::Simplex &simplex, std::vector<int> &faces_id);

std::shared_ptr<std::vector<std::shared_ptr<simplex::SimplexFace>>> createNewFaces(simplex::Simplex &simplex, int i_of_new_point, int max, std::unordered_map<int, int> &table, std::vector<int> &keys);

void sortFaces(simplex::Simplex &simplex, std::vector<int> &sort);

void addToSortList(simplex::Simplex &simplex, int id, std::vector<int> &sort);

}