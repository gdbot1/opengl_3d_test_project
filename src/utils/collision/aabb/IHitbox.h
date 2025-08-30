#pragma once

#include "AABB.h"

namespace aabb {

class IHitbox {
public:
    virtual aabb::AABB getAABB() const = 0;
};

}