#pragma once

#include "utils/collision/aabb/AABB.h"

namespace aabb {

bool collision(const aabb::AABB &hitbox1, const aabb::AABB &hitbox2) {
    return 
	(hitbox1.position.x + hitbox1.size.x >= hitbox2.position.x && hitbox1.position.x < hitbox2.position.x + hitbox2.size.x) &&
	(hitbox1.position.y + hitbox1.size.y >= hitbox2.position.y && hitbox1.position.y < hitbox2.position.y + hitbox2.size.y) &&
	(hitbox1.position.z + hitbox1.size.z >= hitbox2.position.z && hitbox1.position.z < hitbox2.position.z + hitbox2.size.z);
}

}