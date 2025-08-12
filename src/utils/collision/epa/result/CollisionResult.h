#pragma once

#include <glm/glm.hpp>

#include "utils/math/Face.h"

namespace epa {

struct CollisionResult {
    bool status;
    glm::vec3 vector;
    math::Face contact;
    float depth;

    CollisionResult(bool status, const glm::vec3 &vector, float depth, const math::Face &contact) 
	: status(status), vector(vector), depth(depth), contact(contact) {}

    CollisionResult() : status(false), vector(glm::vec3(0, 0, 0)), depth(0.0f), contact() {}

    virtual ~CollisionResult() = default;

    CollisionResult& setStatus(bool status) {
	this->status = status;

	return *this;
    }

    CollisionResult& setVector(const glm::vec3 &vector) {
	this->vector = vector;

	return *this;
    }

    CollisionResult& setDepth(float depth) {
	this->depth = depth;

	return *this;
    }

    CollisionResult& setContact(const glm::vec3 &point1, const glm::vec3 &point2, const glm::vec3 &point3) {
	contact.setFace(point1, point2, point3);

	return *this;
    }
};

}