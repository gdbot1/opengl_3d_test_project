#include "EPAUtils.h"

#include <iostream>

void epa::collision(const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2, epa::CollisionResult &result, int &iterations) {
    simplex::Simplex simplex;

    bool collide_status = gjk::collision(simplex, hitbox1, hitbox2, iterations);

    result.setStatus(collide_status);

    if (!collide_status) {
	return;
    }

    std::vector<int> sort;

    epa::addToSortList(simplex, 0, sort);
    epa::addToSortList(simplex, 1, sort);
    epa::addToSortList(simplex, 2, sort);
    epa::addToSortList(simplex, 3, sort);

    while (iterations > 0) {
	iterations --;

	if (grow(simplex, hitbox1, hitbox2, sort, result)) {//<-
	    break;
	}
    }
}

bool epa::grow(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2, std::vector<int> &sort, epa::CollisionResult &result) {
    if (sort.size() == 0) {
	return true;
    }

    int i_near = sort[0];

    std::shared_ptr<simplex::SimplexFace> nearest_face = simplex.getFace(i_near);

    if (!nearest_face) {
	throw std::runtime_error("EPAUTILS ERROR: grow() error: nearest_face is null (nullptr)");
    }

    glm::vec3 normal = nearest_face->normal;

    if (glm::length(normal) == 0) {
	throw std::runtime_error("EPAUTILS ERROR: grow() error: normal of the nearest face hasn't direction (length == 0)");
    }

    result.setVector(glm::normalize(glm::vec3(normal)));
    result.setDepth(nearest_face->dist + 0.00001f);

    if (simplex::faceIsLookingAtOrigin(simplex, *nearest_face)) {
	normal *= -1;
    }

    glm::vec3 new_point = gjk::getMinkovskiDifferent(hitbox1, hitbox2, normal);

    glm::vec3 point_i1 = simplex.getPoint(nearest_face->i1)->point;

    glm::vec3 vector = math::vectorAB(point_i1, new_point);

    float dist = std::abs(math::distanceTo(vector, normal));

    if (dist <= 0.00001f) {
	return true;
    }

    std::shared_ptr<simplex::SimplexPoint> new_simplex_point = std::make_shared<simplex::SimplexPoint>(new_point);

    simplex.addPoint(new_simplex_point);

    int i_new = simplex.sizePoints() - 1;

    std::vector<int> destroyed_faces;

    std::shared_ptr<std::vector<std::shared_ptr<simplex::SimplexFace>>> new_faces = epa::smashSimplex(simplex, i_new, destroyed_faces);//<-

    for (int i = 0; i < new_faces->size(); i++) {
	simplex.addFace((*new_faces)[i]);
    }

    epa::sortFaces(simplex, sort);

    return false;
}

std::shared_ptr<std::vector<std::shared_ptr<simplex::SimplexFace>>> epa::smashSimplex(simplex::Simplex &simplex, int i_new, std::vector<int> &faces_that_looking_at_new_point) {
    glm::vec3 new_point = simplex.getPoint(i_new)->point;

    epa::getFacesThatLookingAt(simplex, new_point, faces_that_looking_at_new_point);

    std::unordered_map<int, int> table;
    std::vector<int> keys;

    int max = simplex.sizePoints();

    epa::storeEdges(simplex, faces_that_looking_at_new_point, max, table, keys);

    epa::deleteFaces(simplex, faces_that_looking_at_new_point);

    return epa::createNewFaces(simplex, i_new, max, table, keys);//<-
}

void epa::getFacesThatLookingAt(simplex::Simplex &simplex, const glm::vec3 &point, std::vector<int> &faces_id) {
    faces_id.clear();

    for (int i = 0; i < simplex.sizeFaces(); i++) {
	std::shared_ptr<simplex::SimplexFace> face = simplex.getFace(i);

	if (simplex::faceIsLookingAtOrigin(simplex, *face)) {
	    face->normal *= -1;
	}

	if (simplex::faceIsLookingAt(simplex, *face, point)) {
	    faces_id.push_back(i);
	}
    }
}

void epa::storeEdges(const simplex::Simplex &simplex, const std::vector<int> &faces_id, int max, std::unordered_map<int, int> &table, std::vector<int> &keys) {
    //MAX == simplex.points.size()

    for (int i = 0; i < faces_id.size(); i++) {
	simplex::still(*simplex.getFace(faces_id[i]), max, table, keys);
    }
}

void epa::deleteFaces(simplex::Simplex &simplex, std::vector<int> &faces_id) {
    for (int i = 0; i < faces_id.size(); i++) {
	simplex.setFace(nullptr, faces_id[i]);
    }

    for (int i = 0; i < simplex.sizeFaces(); i++) {
	if (simplex.getFace(i) == nullptr) {
	    simplex.removeFace(i);
	    i--;
	}
    }
}

std::shared_ptr<std::vector<std::shared_ptr<simplex::SimplexFace>>> epa::createNewFaces(simplex::Simplex &simplex, int i_of_new_point, int max, std::unordered_map<int, int> &table, std::vector<int> &keys) {
    std::shared_ptr<std::vector<std::shared_ptr<simplex::SimplexFace>>> new_faces = std::make_shared<std::vector<std::shared_ptr<simplex::SimplexFace>>>();

    for (int i = 0; i < keys.size(); i++) {
    	std::cout << "3" << std::endl;
	int hash = keys[i];

	if (table[hash] != 1) {
	    continue;
	}

	int i1 = simplex::getI1(hash, max), i2 = simplex::getI2(hash, max);

	//i1 -> i2- < i_of_new_point

	std::shared_ptr<simplex::SimplexFace> new_face = simplex::createFace(simplex, i1, i2, i_of_new_point);

	if (!new_face) {
	    continue;
	}

	if (simplex::faceIsLookingAtOrigin(simplex, *new_face)) {//<- тут *new_face может быть nullptr, что исправлено if-ом, но это говорит о том, что грань не была создана, а значит либо грань не должна была быть создана, либо есть ошибка, из-за которой грань создаёться не корректно. Nullptr - это сигнал о том, что нормаль новой плоскости не существует, а причиной этому может быть то, что плоскость идёт как 1 линия или точка, либо 1 из точек не доступна (пустая / nullptr).
	    new_face->i2 = i_of_new_point;
	    new_face->i3 = i2;
	    new_face->normal *= -1;
	}

	new_faces->push_back(new_face);
    }

    return new_faces;
}

void epa::sortFaces(simplex::Simplex &simplex, std::vector<int> &sort) {
    sort.clear();

    for (int i = 0; i < simplex.sizeFaces(); i++) {
	epa::addToSortList(simplex, i, sort);
    }
}

void epa::addToSortList(simplex::Simplex &simplex, int id, std::vector<int> &sort) {
    std::shared_ptr<simplex::SimplexFace> face = simplex.getFace(id);

    if (!face) {
	return;
    }

    if (sort.size() == 0) {
	sort.push_back(id);
    }
    else {
	float dist = face->dist;

	for (int i = 0; i < sort.size(); i++) {
	    float curr_dist = simplex.getFace(sort[i])->dist;

	    if (dist < curr_dist) {
		sort.insert(sort.begin() + i, id);
		return;
	    }
	}

	sort.push_back(id);
    }
}