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