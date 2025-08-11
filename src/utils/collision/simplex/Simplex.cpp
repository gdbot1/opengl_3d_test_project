#include "Simplex.h"

#include "utils/collision/simplex/utils/SimplexUtils.h"

void simplex::Simplex::addPoint(std::shared_ptr<simplex::SimplexPoint> point) {
    points.push_back(point);
}

std::shared_ptr<simplex::SimplexPoint> simplex::Simplex::getPoint(int id) const {
    if (id < 0 || id >= points.size()) {
	return nullptr;
    }

    return points[id];
}

int simplex::Simplex::sizePoints() const {
    return points.size();
}

std::vector<std::shared_ptr<simplex::SimplexPoint>>& simplex::Simplex::getPoints() {
    return points;
}

void simplex::Simplex::addFace(std::shared_ptr<simplex::SimplexFace> face) {
    faces.push_back(face);
}

bool simplex::Simplex::addFace(const int i1, const int i2, const int i3) {
/*
    std::shared_ptr<glm::vec3> normal = simplex::findNormal(*this, i1, i2, i3);

    if (!normal || glm::length(*normal) == 0) {
	return false;//ошибка
    }

    std::shared_ptr<simplex::SimplexFace> face = std::make_shared<simplex::SimplexFace>(i1, i2, i3, *normal, 0.0f);

    faces.push_back(face);

    face->dist = *simplex::faceDistanceToOrigin(*this, *face);

    return true;
*/

    std::shared_ptr<simplex::SimplexFace> face = simplex::createFace(*this, i1, i2, i3);

    if (face) {
	faces.push_back(face);

	return true;
    }

    return false;
}

bool simplex::Simplex::addFace(const int i1, const int i2, const int i3, const bool lookAtOutside) {
    return lookAtOutside ? simplex::Simplex::addFace(i1, i2, i3) : simplex::Simplex::addFace(i1, i3, i2);

/*
    if (simplex::Simplex::addFace(i1, i2, i3)) {
	if (lookAtOutside) {
            faces.back()->normal = -faces.back()->normal;
	}
	return true;
    }
    return false;
*/
}

void simplex::Simplex::setFace(std::shared_ptr<SimplexFace> face, int id) {
    while (faces.size() <= id) {
	faces.push_back(nullptr);
    }

    faces[id] = face;
}

std::shared_ptr<simplex::SimplexFace> simplex::Simplex::getFace(int id) const {
    if (id < 0 || id >= faces.size()) {
	return nullptr;
    }

    return faces[id];
}

void simplex::Simplex::removeFace(int id) {
    if (id < 0 || id >= faces.size()) {
	return;
    }

    faces.erase(faces.begin() + id);
}

void simplex::Simplex::removeFace(std::shared_ptr<simplex::SimplexFace> face) {
    for (int i = 0; i < faces.size(); i++) {
	if (faces[i] == face) {
	    simplex::Simplex::removeFace(i);
	    return;
	}
    }
}

int simplex::Simplex::sizeFaces() const {
    return faces.size();
}

std::vector<std::shared_ptr<simplex::SimplexFace>>& simplex::Simplex::getFaces() {
    return faces;
}

void simplex::Simplex::clear() {
    points.clear();
    faces.clear();
}
