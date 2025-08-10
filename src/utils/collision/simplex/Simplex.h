#pragma once

#include <vector>
#include <memory>

#include "utils/collision/simplex/face/SimplexFace.h"
#include "utils/collision/simplex/point/SimplexPoint.h"

namespace simplex {

class Simplex {
public:
    Simplex() = default;

    virtual ~Simplex() = default;

    void addPoint(std::shared_ptr<simplex::SimplexPoint> point);

    std::shared_ptr<simplex::SimplexPoint> getPoint(int id) const;

    int sizePoints() const;

    std::vector<std::shared_ptr<simplex::SimplexPoint>>& getPoints();

    void addFace(std::shared_ptr<simplex::SimplexFace> face);

    bool addFace(const int i1, const int i2, const int i3);

    bool addFace(const int i1, const int i2, const int i3, const bool lookAtOutside);

    void setFace(std::shared_ptr<simplex::SimplexFace> face, int id);

    std::shared_ptr<simplex::SimplexFace> getFace(int id) const;

    void removeFace(int id);

    void removeFace(std::shared_ptr<SimplexFace> face);

    int sizeFaces() const;

    std::vector<std::shared_ptr<simplex::SimplexFace>>& getFaces();

    void clear();
protected:
    std::vector<std::shared_ptr<simplex::SimplexPoint>> points;
    std::vector<std::shared_ptr<simplex::SimplexFace>> faces;
};

}