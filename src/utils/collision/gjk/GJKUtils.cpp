#include "GJKUtils.h"

#include <iostream>

glm::vec3 gjk::getMinkovskiDifferent(const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2, const glm::vec3 direction) {
    glm::vec3 s1 = hitbox1.support(direction);
    glm::vec3 s2 = hitbox2.support(-direction);

    return s1 - s2;
}

bool gjk::collision(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2, int &iterations) {
    glm::vec3 direction = math::vectorAB(hitbox1.getCenter(), hitbox2.getCenter());

    if (glm::length(direction) == 0) {
	direction = glm::vec3(1, 0, 0);
    }

    int i = firstStage(simplex, hitbox1, hitbox2, direction);

    while (iterations > 0) {
	iterations --;

	switch (i) {
	    case 0:
		return false;
	    case 1:
		return true;
	    case 3:
		i = thirdStage(simplex, hitbox1, hitbox2);
		break;
	    case 4:
		i = fourthStage(simplex, hitbox1, hitbox2);
		break;
	}
    }

    return false;
}

bool gjk::collision(const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2) {
    simplex::Simplex simplex;

    int iterations = 20;

    return gjk::collision(simplex, hitbox1, hitbox2, iterations);
}

int gjk::firstStage(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2, glm::vec3 &direction) {
    if (glm::length(direction) == 0) {
	direction = glm::vec3(1, 0, 0);
    }

    glm::vec3 support = gjk::getMinkovskiDifferent(hitbox1, hitbox2, direction);

    std::shared_ptr<simplex::SimplexPoint> new_simplex_point = std::make_shared<simplex::SimplexPoint>(support);

    simplex.addPoint(new_simplex_point);

    return gjk::secondStage(simplex, hitbox1, hitbox2);
}

int gjk::secondStage(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2) {
    std::shared_ptr<simplex::SimplexPoint> simplex_point0 = simplex.getPoint(0);

    glm::vec3 point0 = simplex_point0->point;

    glm::vec3 direction = -point0;

    if (glm::length(direction) == 0) {
	direction = glm::vec3(1, 0, 0);
    }

    glm::vec3 support = gjk::getMinkovskiDifferent(hitbox1, hitbox2, direction);

    float scalar = glm::dot(support, direction);

    if (scalar < 0) {
	return 0;
    }

    std::shared_ptr<simplex::SimplexPoint> new_simplex_point = std::make_shared<simplex::SimplexPoint>(support);

    simplex.addPoint(new_simplex_point);

    return gjk::thirdStage(simplex, hitbox1, hitbox2);
}

int gjk::thirdStage(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2) {
    std::shared_ptr<simplex::SimplexPoint> simplex_point0 = simplex.getPoint(0);
    std::shared_ptr<simplex::SimplexPoint> simplex_point1 = simplex.getPoint(1);

    glm::vec3 point0 = simplex_point0->point;
    glm::vec3 point1 = simplex_point1->point;

    glm::vec3 ob = -point1;
    glm::vec3 ba = math::vectorAB(point1, point0);

    glm::vec3 n = glm::cross(ob, ba);

    glm::vec3 direction = glm::cross(n, ba);

    if (glm::length(direction) == 0) {
	direction = glm::vec3(1, 0, 0);
    }

    float normal_scalar = glm::dot(ob, direction);

    if (normal_scalar < 0) {
	direction = -direction;
    }

    glm::vec3 support = gjk::getMinkovskiDifferent(hitbox1, hitbox2, direction);

    float scalar = glm::dot(support, direction);

    if (scalar < 0) {
	return 0;
    }

    std::shared_ptr<simplex::SimplexPoint> new_simplex_point = std::make_shared<simplex::SimplexPoint>(support);

    simplex.addPoint(new_simplex_point);

    simplex.addFace(0, 1, 2);

    return fourthStage(simplex, hitbox1, hitbox2);
}

int gjk::fourthStage(simplex::Simplex &simplex, const gjk::IHitbox &hitbox1, const gjk::IHitbox &hitbox2) {
    std::shared_ptr<simplex::SimplexFace> face0 = simplex.getFace(0);

    glm::vec3 normal = face0->normal;

    if (glm::length(normal) == 0) {
	return 0;
    }

    glm::vec3 direction = normal;

    bool normalLookingOutside = !simplex::faceIsLookingAtOrigin(simplex, *face0);

    if (normalLookingOutside) {
	direction = -normal;
    }
    else {
	face0->normal = -face0->normal;
    }

    if (glm::length(direction) == 0) {
	direction = glm::vec3(1, 0, 0);
    }

    glm::vec3 support = gjk::getMinkovskiDifferent(hitbox1, hitbox2, direction);

    float scalar = glm::dot(support, direction);

    if (scalar < 0) {
	return 0;
    }

    std::shared_ptr<simplex::SimplexPoint> new_simplex_point = std::make_shared<simplex::SimplexPoint>(support);

    simplex.addPoint(new_simplex_point);

    simplex.addFace(0, 3, 1, normalLookingOutside);
    simplex.addFace(1, 3, 2, normalLookingOutside);
    simplex.addFace(2, 3, 0, normalLookingOutside);

    return finalStage(simplex);
}

int gjk::finalStage(simplex::Simplex &simplex) {
    if (simplex.sizeFaces() != 4) {
	throw std::runtime_error("GJKUTILS ERROR: finalStage() error: simplex.sizeFaces() isn't equals 4. Tetrahedron must have 4 faces");
    }

    std::vector<std::shared_ptr<simplex::SimplexFace>> outer_faces, inner_faces;

    for (int i = 1; i < 4; i++) {
	std::shared_ptr<simplex::SimplexFace> face = simplex.getFace(i);

	std::shared_ptr<simplex::SimplexPoint> face_point0 = simplex.getPoint(face->i1);

	glm::vec3 vector = -face_point0->point;

	glm::vec3 normal = face->normal;

	float scalar = glm::dot(vector, normal);

	if (scalar < 0) {
	    inner_faces.push_back(face);
	}
	else {
	    outer_faces.push_back(face);
	}
    }

    if (inner_faces.size() == 3) {//внутри для всех 3 граней (4 грань находиться снизу, и для неё центр всегда внутри)
	return 1;
    }
    else if (outer_faces.size() == 1) {
	std::shared_ptr<simplex::SimplexFace> face = outer_faces[0];

	int i1 = face->i1, i2 = face->i2, i3 = face->i3;

	std::shared_ptr<simplex::SimplexPoint> point1 = simplex.getPoint(i1), point2 = simplex.getPoint(i2), point3 = simplex.getPoint(i3);

	simplex.clear();

	simplex.addPoint(point1);
	simplex.addPoint(point2);
	simplex.addPoint(point3);

	simplex.addFace(0, 1, 2);

	return 4;
    }
    else if (outer_faces.size() == 2) {
	std::pair<int, int> sameEdge = simplex::getSameEdge(*outer_faces[0], *outer_faces[1]);

	if (sameEdge.first == -1 || sameEdge.second == -1) {
	    throw std::runtime_error("GJKUTILS ERROR: finalStage() error: origin is out of 2 faces, and 2 faces hasn't the same edge");
	}

	std::shared_ptr<simplex::SimplexPoint> point1 = simplex.getPoint(sameEdge.first);
	std::shared_ptr<simplex::SimplexPoint> point2 = simplex.getPoint(sameEdge.second);

	simplex.clear();

	simplex.addPoint(point2);
	simplex.addPoint(point1);

	return 3;
    }
    else {
	return 0;
    }
}