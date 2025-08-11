#include "SimplexUtils.h"

bool simplex::faceIsLookingAt(simplex::Simplex &simplex, simplex::SimplexFace &face, const glm::vec3 at) {
    glm::vec3 point_i1 = simplex.getPoint(face.i1)->point;
    glm::vec3 vector = math::vectorAB(point_i1, at);

    float scalar = glm::dot(vector, face.normal);

    return scalar > 0;
}

bool simplex::faceIsLookingAtOrigin(simplex::Simplex &simplex, simplex::SimplexFace &face) {
    return faceIsLookingAt(simplex, face, glm::vec3(0, 0, 0));
}

std::shared_ptr<glm::vec3> simplex::findNormal(simplex::Simplex &simplex, const int i1, const int i2, const int i3) {
    std::shared_ptr<simplex::SimplexPoint> p1 = simplex.getPoint(i1), p2 = simplex.getPoint(i2), p3 = simplex.getPoint(i3);

    if (!p1 || !p2 || !p3) {
	return nullptr;
    }

    glm::vec3 v1 = math::vectorAB(p1->point, p2->point);
    glm::vec3 v2 = math::vectorAB(p1->point, p3->point);

    return std::make_shared<glm::vec3>(glm::cross(v1, v2));
}

std::shared_ptr<float> simplex::faceDistanceToOrigin(simplex::Simplex &simplex, simplex::SimplexFace &face) {
    if (glm::length(face.normal) == 0) {
	return nullptr;
    }

    glm::vec3 vector = -simplex.getPoint(face.i1)->point;

    return std::make_shared<float>(abs(math::distanceTo(vector, face.normal)));
}

std::pair<int, int> simplex::getSameEdge(simplex::SimplexFace &face1, simplex::SimplexFace &face2) {
    auto ver1 = face1.getVertices(), ver2 = face2.getVertices();

    int count = 0;

    std::pair<int, int> edge{-1, -1};

    for (int i = 0; i < ver1.size(); i++) {
	for (int j = 0; j < ver2.size(); j++) {
	    if (ver1[i] == ver2[j]) {
		switch (count) {
		    case 0:
			edge.first = ver1[i];
			break;
		    case 1:
			edge.second = ver1[i];
			break;

		    default:
			return edge;
		}

		count ++;
	    }
	}
    }

    return edge;
}

int simplex::getEdgeUniqueHashcode(int a, int b, int max_i) {
    return std::min(a, b) * max_i + std::max(a, b);
}

void simplex::stillOne(int a, int b, int max_i, std::unordered_map<int, int> &table, std::vector<int> &keys) {
    int hash = simplex::getEdgeUniqueHashcode(a, b, max_i);

    if (table.find(hash) == table.end()) {
	table[hash] = 1;
	keys.push_back(hash);
    }
    else {
	table[hash]++;
    }
}

void simplex::still(simplex::SimplexFace &face, int max_i, std::unordered_map<int, int> &table, std::vector<int> &keys) {
    simplex::stillOne(face.i1, face.i2, max_i, table, keys);
    simplex::stillOne(face.i2, face.i3, max_i, table, keys);
    simplex::stillOne(face.i3, face.i1, max_i, table, keys);
}

int simplex::getI1(int hash, int max_i) {
    return hash / max_i;
}

int simplex::getI2(int hash, int max_i) {
    return hash % max_i;
}

std::shared_ptr<simplex::SimplexFace> simplex::createFace(simplex::Simplex &simplex, int i1, int i2, int i3) {
    std::shared_ptr<glm::vec3> normal = simplex::findNormal(simplex, i1, i2, i3);

    if (!normal || glm::length(*normal) == 0) {
	return nullptr;
    }

    std::shared_ptr<simplex::SimplexFace> face = std::make_shared<simplex::SimplexFace>(i1, i2, i3, *normal, 0.0f);

    face->dist = *simplex::faceDistanceToOrigin(simplex, *face);

    return face;
}